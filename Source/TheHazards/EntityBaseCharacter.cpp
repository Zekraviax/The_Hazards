#include "EntityBaseCharacter.h"


#include "ActorComponentBaseStats.h"
#include "ActorComponentInventory.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "DrawDebugHelpers.h"
#include "EntityPlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/InputSettings.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "WidgetHudBattle.h"
#include "WidgetMenuPause.h"


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
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));

	// Create a gun mesh component
	FP_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
	FP_Gun->bCastDynamicShadow = false;
	FP_Gun->CastShadow = false;
	FP_Gun->SetupAttachment(RootComponent);

	FP_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	FP_MuzzleLocation->SetupAttachment(FP_Gun);
	FP_MuzzleLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));

	// Default offset from the character location for projectiles to spawn
	GunOffset = FVector(100.0f, 0.0f, 10.0f);

	// Gameplay components
	BaseStatsComponent = CreateDefaultSubobject<UActorComponentBaseStats>(TEXT("EntityBaseStats"));
	BaseStatsComponent->SetIsReplicated(true);

	InventoryComponent = CreateDefaultSubobject<UActorComponentInventory>(TEXT("EntityInventory"));
	InventoryComponent->SetIsReplicated(true);

	// Multiplayer
	bReplicates = true;

	// Note: The ProjectileClass and the skeletal mesh/anim blueprints for Mesh1P, FP_Gun, and VR_Gun 
	// are set in the derived blueprint asset named MyCharacter to avoid direct content references in C++.
}


void AEntityBaseCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Each property of the character that is replicated needs to be specified here
	DOREPLIFETIME(AEntityBaseCharacter, Mesh1P);
	DOREPLIFETIME(AEntityBaseCharacter, FP_Gun);
}


void AEntityBaseCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Attach gun mesh component to Skeleton, doing it here because the skeleton is not yet created in the constructor
	FP_Gun->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
}


void AEntityBaseCharacter::OnFire()
{
	float WeaponDamagePerShot = 1.f;
	float DelayUntilNextAttack = 0.25f;

	// Use LineTraces for to determine where weapon shot will land
	// Two FHitResults will store all data returned by our line traces
	FHitResult FirstHit, Hit;

	// Use QueryParams to prevent this entity from being hit by it's own line trace
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	// First line trace: Find the actor/object the entity is directly looking at
	TArray<AActor*> ActorsToIgnore;

	FVector TraceStart = FirstPersonCameraComponent->GetComponentLocation();
	FVector TraceEnd = FirstPersonCameraComponent->GetComponentLocation() + FirstPersonCameraComponent->GetForwardVector() * 10000.0f;
	UKismetSystemLibrary::LineTraceSingle(this, TraceStart, TraceEnd, UEngineTypes::ConvertToTraceType(ECC_Camera), false, ActorsToIgnore, EDrawDebugTrace::None, FirstHit, true);

	// Second line trace: Simulate firing a weapon
	// Draw a line starting from this entity's gun muzzle position and finishing at the thing directly ahead
	TraceStart = ((FP_MuzzleLocation != nullptr) ? FP_MuzzleLocation->GetComponentLocation() : GetActorLocation()) + GetControlRotation().RotateVector(GunOffset);
	TraceEnd = FirstHit.Location;

	// LineTraceSingleByChannel returns the first actor hit within the chosen collision channel
	GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, ECollisionChannel::ECC_Pawn);

	// Use DrawDebugLine to show the line trace
	DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, false, 2.5f);


	// Use this entity's inventory component to get their weapon's stats, sounds, etc.
	if (GetInventoryComponent()) {
		GetInventoryComponent()->ReturnEquippedWeaponsData(WeaponDamagePerShot);
	}

	
	// try and play the sound if specified
	if (FireSound != NULL) {
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}

	// try and play a firing animation if specified
	if (FireAnimation != NULL) {
		// Get the animation object for the arms mesh
		UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance();
		if (AnimInstance != NULL) {
			AnimInstance->Montage_Play(FireAnimation, 1.f);
		}
	}

	// If the line trace connects with a valid entity, deal damage to them
	if (Cast<AEntityBaseCharacter>(Hit.Actor.Get())) {
		Cast<AEntityBaseCharacter>(Hit.Actor.Get())->ReceiveDamage(WeaponDamagePerShot, this);
	}

	// Set a timer to automatically fire the weapon
	GetWorld()->GetTimerManager().SetTimer(AutomaticWeaponFireTimerHandle, this, &AEntityBaseCharacter::OnFire, DelayUntilNextAttack, false);
}


void AEntityBaseCharacter::OnStopFiring()
{
	GetWorld()->GetTimerManager().ClearTimer(AutomaticWeaponFireTimerHandle);
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


void AEntityBaseCharacter::EntityAddYawInput(float Val)
{
	if (Val != 0.f && Controller && Controller->IsLocalPlayerController())
	{
		APlayerController* const PC = CastChecked<APlayerController>(Controller);

		if (IsCharging) {
			PC->AddYawInput(Val * 0.1f);
		} else {
			PC->AddYawInput(Val);
		}
	}
}


void AEntityBaseCharacter::EntityAddPitchInput(float Val)
{
	if (Val != 0.f && Controller && Controller->IsLocalPlayerController())
	{
		APlayerController* const PC = CastChecked<APlayerController>(Controller);

		if (IsCharging) {
			PC->AddPitchInput(Val * 0.1f);
		} else {
			PC->AddPitchInput(Val);
		}
	}
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


void AEntityBaseCharacter::OnJumpBegin()
{
	Jump();

	if (IsSprinting) {
		LaunchCharacter(FVector(GetActorForwardVector().X * 500.f, GetActorForwardVector().Y * 500.f, 750.f), false, false);
	}
}


void AEntityBaseCharacter::OnChargeBeginHeldDown()
{
	// Tick up the Charge timer if the player is holding down the Charge button
	UE_LOG(LogTemp, Warning, TEXT("OnChargeBegin()  /  Entity begun winding up for charge"));

	GetWorld()->GetTimerManager().SetTimer(BeginChargeTimerHandle, this, &AEntityBaseCharacter::OnChargeEndHeldDown, 10.f, false);
}


void AEntityBaseCharacter::OnChargeEndHeldDown()
{
	// Launch the player forward if they've held the Charge button down for the minimum required time and the button is released
	UE_LOG(LogTemp, Warning, TEXT("OnChargeEnd()  /  Entity begun sprinting"));

	GetWorld()->GetTimerManager().SetTimer(ChargeTimerHandle, this, &AEntityBaseCharacter::OnChargeTimerReachedZero, GetWorld()->GetTimerManager().GetTimerElapsed(BeginChargeTimerHandle), false);
	GetWorld()->GetTimerManager().ClearTimer(BeginChargeTimerHandle);

	if (GetCharacterMovement()->MaxWalkSpeed != BaseMoveSpeed * 6) {
		GetCharacterMovement()->MaxWalkSpeed += BaseMoveSpeed * 6;

		// Set acceleration to be near-instant

		// Set turn rate to be very low
		//BaseTurnRate = 4.5f;
	}

	IsCharging = true;
}


void AEntityBaseCharacter::OnChargeTimerReachedZero()
{
	UE_LOG(LogTemp, Warning, TEXT("OnChargeEnd()  /  Entity finished sprinting"));

	if (GetCharacterMovement()->MaxWalkSpeed != BaseMoveSpeed) {
		GetCharacterMovement()->MaxWalkSpeed = BaseMoveSpeed;

		// Set acceleration to be normal

		// Set turn rate to be normal
		//BaseTurnRate = 45.f;
	}

	IsCharging = false;

	// To-Do: End a charge if the charger runs in to an obstacle
	// or if a charging player releases the move forward key
}


void AEntityBaseCharacter::ReceiveDamage(float Damage, AEntityBaseCharacter* Source)
{
	GetBaseStatsComponent()->UpdateCurrentHealthPoints(Damage * -1.f);

	// To-Do: Handle deaths for NPCs and players
	if (GetBaseStatsComponent()->CurrentHealthPoints <= 0.0f) {
		// To-Do: For each level, create a pool of entities that are loaded when the level is
		// When one of those entities dies, return it to the pool instead of destroying it
		Destroy();

		if (Cast<AEntityPlayerCharacter>(Source)) {
			Cast<AEntityPlayerCharacter>(Source)->GetBaseStatsComponent()->UpdateCurrentExperiencePoints(50);
			Cast<AEntityPlayerCharacter>(Source)->GetBaseStatsComponent()->UpdateCredits(50);
			Cast<AEntityPlayerCharacter>(Source)->GetBaseStatsComponent()->UpdateScrap(50);
		}
	}
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
	// Prevent entity from sprinting if they don't have any AP
	// If they run out of AP mid-sprint, stop them from sprinting
	if (IsSprinting && GetMovementComponent()->IsMovingOnGround() && GetVelocity().Size() > 0.f) {
		if (GetBaseStatsComponent()->CurrentAuraPoints > 0.f) {
			BaseStatsComponent->UpdateCurrentAuraPoints(LerpRate * -1);
		} else {
			OnSprintEnd();
		}
	}

	// if 
}