#include "EntityBaseCharacter.h"

#include "TheHazardsProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/InputSettings.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);


//////////////////////////////////////////////////////////////////////////
// AEntityBaseCharacter
AEntityBaseCharacter::AEntityBaseCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetRootComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, CharacterHeight)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);			// only the owning player will see this mesh
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));

	// Create a gun mesh component
	FP_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
	FP_Gun->SetOnlyOwnerSee(true);			// only the owning player will see this mesh
	FP_Gun->bCastDynamicShadow = false;
	FP_Gun->CastShadow = false;
	FP_Gun->SetupAttachment(RootComponent);

	FP_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	FP_MuzzleLocation->SetupAttachment(FP_Gun);
	FP_MuzzleLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));

	// Default offset from the character location for projectiles to spawn
	GunOffset = FVector(100.0f, 0.0f, 10.0f);

	// Note: The ProjectileClass and the skeletal mesh/anim blueprints for Mesh1P, FP_Gun, and VR_Gun 
	// are set in the derived blueprint asset named MyCharacter to avoid direct content references in C++.
}


void AEntityBaseCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Attach gun mesh component to Skeleton, doing it here because the skeleton is not yet created in the constructor
	FP_Gun->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));

	// Show or hide the two versions of the gun based on whether or not we're using motion controllers.
	// FPS template would show or hide this mesh based on whether or not we're using motion controllers
	// To-Do: Test if this can be moved to the constructor or deleted
	Mesh1P->SetHiddenInGame(false, true);
}


//////////////////////////////////////////////////////////////////////////
// Input
void AEntityBaseCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Bind fire event
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AEntityBaseCharacter::OnFire);

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &AEntityBaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AEntityBaseCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AEntityBaseCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AEntityBaseCharacter::LookUpAtRate);

	// Begin and end crouching
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AEntityBaseCharacter::OnCrouchBegin);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &AEntityBaseCharacter::OnCrouchEnd);

	// Begin and end sprinting
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AEntityBaseCharacter::OnSprintBegin);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AEntityBaseCharacter::OnSprintEnd);
}


void AEntityBaseCharacter::Tick(float DeltaTime)
{
	// Adjust height if crouching
	if (IsCrouching && LerpValue < 1) {
		// At a rate of 0.01 per tick, and a rate of 60 ticks per second,
		// it should take 1.4 seconds to reach maximum crouch
		LerpValue += LerpRate;

		FirstPersonCameraComponent->SetRelativeLocation(FMath::Lerp(
			FVector(
			FirstPersonCameraComponent->GetRelativeLocation().X, 
			FirstPersonCameraComponent->GetRelativeLocation().Y, 
			CharacterHeight),
			FVector(
			FirstPersonCameraComponent->GetRelativeLocation().X,
			FirstPersonCameraComponent->GetRelativeLocation().Y,
			(CharacterHeight / 2)),
			LerpValue
		));
	} else if (!IsCrouching && LerpValue > 0) {
		LerpValue -= LerpRate;

		FirstPersonCameraComponent->SetRelativeLocation(FMath::Lerp(
			FVector(
				FirstPersonCameraComponent->GetRelativeLocation().X,
				FirstPersonCameraComponent->GetRelativeLocation().Y,
				CharacterHeight),
			FVector(
				FirstPersonCameraComponent->GetRelativeLocation().X,
				FirstPersonCameraComponent->GetRelativeLocation().Y,
				(CharacterHeight / 2)),
			LerpValue
		));
	}

	// Drain AP if sprinting
}


void AEntityBaseCharacter::OnFire()
{
	// Use LineTraces for weapon fire

	// FHitResult will store all data returned by our line trace
	FHitResult Hit;

	// Draw a line starting from this entity's position and finishing 1000cm ahead of it
	FVector TraceStart = GetActorLocation();
	FVector TraceEnd = GetActorLocation() + GetActorForwardVector() * 1000.0f;


	// try and fire a projectile
	//if (ProjectileClass != NULL) {
	//	UWorld* const World = GetWorld();

	//	if (World != NULL) {
	//		const FRotator SpawnRotation = GetControlRotation();
	//		// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
	//		const FVector SpawnLocation = ((FP_MuzzleLocation != nullptr) ? FP_MuzzleLocation->GetComponentLocation() : GetActorLocation()) + SpawnRotation.RotateVector(GunOffset);

	//		//Set Spawn Collision Handling Override
	//		FActorSpawnParameters ActorSpawnParams;
	//		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

	//		// spawn the projectile at the muzzle
	//		World->SpawnActor<ATheHazardsProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
	//	}
	//}

	

	// try and play the sound if specified
	if (FireSound != NULL) {
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}

	// try and play a firing animation if specified
	if (FireAnimation != NULL) {
		// Get the animation object for the arms mesh
		UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance();
		if (AnimInstance != NULL)
		{
			AnimInstance->Montage_Play(FireAnimation, 1.f);
		}
	}
}


void AEntityBaseCharacter::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
	}
}


void AEntityBaseCharacter::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}


void AEntityBaseCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}


void AEntityBaseCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}


void AEntityBaseCharacter::OnCrouchBegin()
{
	UE_LOG(LogTemp, Warning, TEXT("OnCrouchBegin()  /  Entity begun crouching"));

	if (!IsSprinting) {
		IsCrouching = true;

		GetCharacterMovement()->MaxWalkSpeed = BaseMoveSpeed * 0.5;
	}
}


void AEntityBaseCharacter::OnCrouchEnd()
{
	UE_LOG(LogTemp, Warning, TEXT("OnCrouchEnd()  /  Entity finished crouching"));

	IsCrouching = false;

	GetCharacterMovement()->MaxWalkSpeed = BaseMoveSpeed;
}


void AEntityBaseCharacter::OnSprintBegin()
{
	UE_LOG(LogTemp, Warning, TEXT("OnSprintBegin()  /  Entity begun sprinting"));

	if (!IsCrouching) {
		IsSprinting = true;

		GetCharacterMovement()->MaxWalkSpeed = BaseMoveSpeed * 1.5;
	}
}


void AEntityBaseCharacter::OnSprintEnd()
{
	UE_LOG(LogTemp, Warning, TEXT("OnSprintEnd()  /  Entity finished sprinting"));

	IsSprinting = false;

	GetCharacterMovement()->MaxWalkSpeed = BaseMoveSpeed;
}