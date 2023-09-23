#include "EntityBaseCharacter.h"


#include "ActorComponentBaseData.h"
#include "ActorComponentBaseStats.h"
#include "ActorComponentInventory.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "DrawDebugHelpers.h"
#include "FunctionLibrarySpecialAttacks.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/InputSettings.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "WidgetHudBattle.h"
#include "WidgetMenuPause.h"


class AEntityPlayerCharacter;


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

	// Create a melee weapon component
	MeleeWeaponHitbox = CreateDefaultSubobject<UBoxComponent>(TEXT("MeleeWeaponHitbox"));
	MeleeWeaponHitbox->SetGenerateOverlapEvents(false);
	MeleeWeaponHitbox->SetupAttachment(RootComponent);
	MeleeWeaponHitbox->bHiddenInGame = false;
	MeleeWeaponHitbox->OnComponentBeginOverlap.AddDynamic(this, &AEntityBaseCharacter::BoxComponentBeginOverlap);

	// Default offset from the character location for projectiles to spawn
	GunOffset = FVector(100.0f, 0.0f, 10.0f);

	InteractBounds = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractBounds"));
	InteractBounds->SetupAttachment(GetRootComponent());

	// Gameplay components
	BaseDataComponent = CreateDefaultSubobject<UActorComponentBaseData>(TEXT("EntityBaseData"));
	BaseDataComponent->SetIsReplicated(true);

	BaseStatsComponent = CreateDefaultSubobject<UActorComponentBaseStats>(TEXT("EntityBaseStats"));
	BaseStatsComponent->SetIsReplicated(true);

	InventoryComponent = CreateDefaultSubobject<UActorComponentInventory>(TEXT("EntityInventory"));
	InventoryComponent->SetIsReplicated(true);

	// Multiplayer
	bReplicates = true;
}


void AEntityBaseCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Each property of the character that is replicated needs to be specified here
	DOREPLIFETIME(AEntityBaseCharacter, Mesh1P);
	DOREPLIFETIME(AEntityBaseCharacter, FP_Gun);
	//DOREPLIFETIME(AEntityBaseCharacter, MeleeWeaponHitbox);
}


void AEntityBaseCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	// Bind delegates
	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &AEntityBaseCharacter::OnCapsuleComponentHit);

	// Attach gun mesh component to Skeleton, doing it here because the skeleton is not yet created in the constructor
	FP_Gun->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
	MeleeWeaponHitbox->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));
	MeleeWeaponHitbox->AddRelativeLocation(FVector(0.f, 100.f, 0.f));
	MeleeWeaponHitbox->SetWorldScale3D(FVector(1.f, 3.f, 1.f));
}


void AEntityBaseCharacter::OnCapsuleComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("AEntityBaseCharacter / OnCapsuleComponentHit / Collided With Actor: %s"), *OtherActor->GetName()));

	if (IsCharging) {
		GetMovementComponent()->Velocity = FVector(0, 0, 0);

		OnChargeTimerReachedZero();
		GetWorld()->GetTimerManager().ClearTimer(BeginChargeTimerHandle);

		if (Cast<AEntityBaseCharacter>(OtherActor)) {
			Cast<AEntityBaseCharacter>(OtherActor)->ReceiveDamage(150.f, this);
		} else {
			OnStunBegin();
		}
	}
}


void AEntityBaseCharacter::BoxComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	MeleeWeaponHit(OtherActor);
}


void AEntityBaseCharacter::MeleeWeaponHit(AActor* OtherActor)
{
	if (OtherActor != this && !ActorsToIgnore.Contains(OtherActor)) {
		float WeaponDamage = 1.f;

		// Use this entity's inventory component to get their weapon's stats, sounds, etc.
		if (GetInventoryComponent()) {
			GetInventoryComponent()->ReturnEquippedWeaponNormalDamage(WeaponDamage);
		}

		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("AEntityBaseCharacter / BoxComponentBeginOverlap / Overlapped With Actor: %s"), *OtherActor->GetName()));

		Cast<AEntityBaseCharacter>(OtherActor)->ReceiveDamage(WeaponDamage, this);
		ActorsToIgnore.Add(OtherActor);
	}
}


void AEntityBaseCharacter::OnFire()
{
	EWeaponAttackStyles AttackStyle = EWeaponAttackStyles::Melee;

	if (AttackStyle == EWeaponAttackStyles::Melee) {
	}

	float WeaponDamagePerShot = 1.f;
	float DelayUntilNextAttack = 0.25f;
	float MeleeWeaponAnimationTime = 1.f;


	// Use LineTraces for to determine where weapon shot will land
	// Two FHitResults will store all data returned by our line traces
	FHitResult FirstHit, Hit;

	// Use QueryParams to prevent this entity from being hit by it's own line trace
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);

	// Use this entity's inventory component to get their weapon's stats, sounds, etc.
	if (GetInventoryComponent()) {
		GetInventoryComponent()->ReturnEquippedWeaponNormalDamage(WeaponDamagePerShot);
	}

	ActorsToIgnore.Empty();

	if (AttackStyle == EWeaponAttackStyles::Ranged) {
		// First line trace: Find the actor/object the entity is directly looking at

		FVector TraceStart = FirstPersonCameraComponent->GetComponentLocation();
		FVector TraceEnd = FirstPersonCameraComponent->GetComponentLocation() + FirstPersonCameraComponent->GetForwardVector() * 1000000.0f;
		UKismetSystemLibrary::LineTraceSingle(this, TraceStart, TraceEnd, UEngineTypes::ConvertToTraceType(ECC_Camera), false, ActorsToIgnore, EDrawDebugTrace::None, FirstHit, true);

		// Second line trace: Simulate firing a weapon
		// Draw a line starting from this entity's gun muzzle position and finishing at the thing directly ahead
		// (Dev note: line traces fail if they don't hit anything, so each level needs invisible boxes around it.)
		TraceStart = ((FP_MuzzleLocation != nullptr) ? FP_MuzzleLocation->GetComponentLocation() : GetActorLocation()) + GetControlRotation().RotateVector(GunOffset);
		TraceEnd = FirstHit.Location;

		// LineTraceSingleByChannel returns the first actor hit within the chosen collision channel
		GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, ECollisionChannel::ECC_Pawn);

		// Use DrawDebugLine to show the line trace
		DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, false, 2.5f);

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
	} else if (AttackStyle == EWeaponAttackStyles::Melee) {
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("AEntityBaseCharacter / OnFire / Begin Melee Attack")));

		MeleeWeaponHitbox->SetGenerateOverlapEvents(true);

		// Set a timer which prevents the player from swinging a melee weapon if they're currently mid-swing
		GetWorld()->GetTimerManager().SetTimer(MeleeWeaponSwingTimerHandle, this, &AEntityBaseCharacter::OnMeleeWeaponSwingEnd, MeleeWeaponAnimationTime, false);
		
		// The delay until the next attack is always slightly longer than the attack time itself
		// in order to pre-emptively avoid issues with the melee hitbox not being overlappable
		DelayUntilNextAttack = MeleeWeaponAnimationTime + 0.02f;
	}

	
	// try and play the sound if specified
	if (FireSound != NULL) {
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}

	// Set a timer to automatically fire the weapon again for as long as the fire button is held
	if (Cast<AEntityPlayerCharacter>(this)) {
		GetWorld()->GetTimerManager().SetTimer(RangedWeaponFireTimerHandle, this, &AEntityBaseCharacter::OnFire, DelayUntilNextAttack, false);
	}
}


void AEntityBaseCharacter::OnStopFiring()
{
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("AEntityBaseCharacter / OnStopFiring / Player Released Fire Button")));

	GetWorld()->GetTimerManager().ClearTimer(RangedWeaponFireTimerHandle);
	GetWorld()->GetTimerManager().ClearTimer(MeleeWeaponSwingTimerHandle);
}


void AEntityBaseCharacter::OnMeleeWeaponSwingEnd()
{
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("AEntityBaseCharacter / OnMeleeWeaponSwingEnd / Melee Attack Animation Finished")));

	MeleeWeaponHitbox->SetGenerateOverlapEvents(false);
}


void AEntityBaseCharacter::OnLaunchSpecialAttack()
{
	if (MeleeWeaponHitbox->GetGenerateOverlapEvents() == false) {
		// Get the player's weapon data here
		EWeaponTypes WeaponType = EWeaponTypes::Sickle;
		FVector SpecialAttackMeleeHitBoxScale = FVector(4.f, 2.f, 4.f);
		float SpecialAttackDuration = 1.f;

		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("AEntityBaseCharacter / OnLaunchSpecialAttack / Begin Special Attack")));

		switch (WeaponType) {
		case (EWeaponTypes::Sickle):
			//UFunctionLibrarySpecialAttacks::SickleSpecialAttackBegin(this);

			MeleeWeaponHitbox->SetWorldScale3D(SpecialAttackMeleeHitBoxScale);
			MeleeWeaponHitbox->SetGenerateOverlapEvents(true);
			break;
		default:
			break;
		}

		GetWorld()->GetTimerManager().SetTimer(SpecialAttackTimerHandle, this, &AEntityBaseCharacter::OnSpecialAttackEnd, SpecialAttackDuration, false);
	}
}


void AEntityBaseCharacter::OnSpecialAttackEnd()
{
	FVector NormalMeleeHitBoxScale = FVector(2.f, 1.f, 1.f);

	MeleeWeaponHitbox->SetWorldScale3D(NormalMeleeHitBoxScale);
	MeleeWeaponHitbox->SetGenerateOverlapEvents(false);

	ActorsToIgnore.Empty();
}


void AEntityBaseCharacter::MoveForward(float Value)
{
	//MoveForwardValue = Value;

	if (Value != 0.0f && !IsStunned)
	{
		// add movement in that direction
		AddMovementInput(GetActorForwardVector(), Value);
		MoveForwardHeldDown = true;
	} else {
		MoveForwardHeldDown = false;
	}
}


void AEntityBaseCharacter::MoveRight(float Value)
{
	MoveRightValue = Value;

	if (Value != 0.0f && !IsStunned)
	{
		// add movement in that direction
		AddMovementInput(GetActorRightVector(), Value);
	}
}


void AEntityBaseCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	if (!IsStunned) {
		AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
	}
}


void AEntityBaseCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	if (!IsStunned) {
		AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
	}
}


void AEntityBaseCharacter::EntityAddYawInput(float Val)
{
	if (Val != 0.f && Controller && Controller->IsLocalPlayerController() && !IsStunned)
	{
		APlayerController* const PC = CastChecked<APlayerController>(Controller);

		if (IsCharging) {
			PC->AddYawInput(Val * 0.05f);
		} else {
			PC->AddYawInput(Val);
		}
	}
}


void AEntityBaseCharacter::EntityAddPitchInput(float Val)
{
	if (Val != 0.f && Controller && Controller->IsLocalPlayerController() && !IsStunned)
	{
		APlayerController* const PC = CastChecked<APlayerController>(Controller);

		if (IsCharging) {
			PC->AddPitchInput(Val * 0.05f);
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
	if (!IsCrouching) {
		if (MoveForwardHeldDown) {
			UE_LOG(LogTemp, Warning, TEXT("OnSprintBegin()  /  Entity begun sprinting"));

			IsSprinting = true;
			GetCharacterMovement()->MaxWalkSpeed = BaseMoveSpeed * 1.5;
		} else {
			if (GetWorld()->GetTimerManager().GetTimerElapsed(BeginChargeTimerHandle) <= 0.f && GetWorld()->GetTimerManager().GetTimerElapsed(ChargeTimerHandle) <= 0.f) {
				OnChargeBeginHeldDown();
			}
		}
	}
}


void AEntityBaseCharacter::OnSprintEnd()
{
	UE_LOG(LogTemp, Warning, TEXT("OnSprintEnd()  /  Entity finished sprinting"));

	IsSprinting = false;
	GetCharacterMovement()->MaxWalkSpeed = BaseMoveSpeed;

	if (GetWorld()->GetTimerManager().GetTimerElapsed(BeginChargeTimerHandle) > 0.f) {
		OnChargeEndHeldDown();
	}
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


void AEntityBaseCharacter::OnStunBegin()
{
	IsStunned = true;

	GetWorld()->GetTimerManager().SetTimer(StunTimerHandle, this, &AEntityBaseCharacter::OnStunEnd, 2.f, false);
}


void AEntityBaseCharacter::OnStunEnd()
{
	IsStunned = false;
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
	if (GetWorld()->GetTimerManager().GetTimerElapsed(StunTimerHandle) >= 0.f) {
		GEngine->AddOnScreenDebugMessage(-1, 0.15f, FColor::Red, FString::Printf(TEXT("AEntityBaseCharacter / Tick / Stun Timer: %f"), GetWorld()->GetTimerManager().GetTimerElapsed(StunTimerHandle)));
	}

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
	//GEngine->AddOnScreenDebugMessage(-1, 0.15f, FColor::Red, FString::Printf(TEXT("AEntityBaseCharacter / Tick / IsSprinting?: %s"), IsSprinting ? TEXT("True") : TEXT("False")));
	//GEngine->AddOnScreenDebugMessage(-1, 0.15f, FColor::Red, FString::Printf(TEXT("AEntityBaseCharacter / Tick / IsMovingOnGround?: %s"), GetMovementComponent()->IsMovingOnGround() ? TEXT("True") : TEXT("False")));
	//GEngine->AddOnScreenDebugMessage(-1, 0.15f, FColor::Red, FString::Printf(TEXT("AEntityBaseCharacter / Tick / Velocity: %d"), GetVelocity().Size()));
	if (IsSprinting && GetMovementComponent()->IsMovingOnGround() && GetVelocity().Size() > 0.f) {
		if (GetBaseStatsComponent()->CurrentAuraPoints > 0.f) {
			BaseStatsComponent->UpdateCurrentAuraPoints(LerpRate * -1);
		} else {
			OnSprintEnd();
		}
	}

	// if 

	// For any entities that are already overlapping the melee hitbox at the start attack,
	// damage them immediately
	MeleeWeaponHitbox->GetOverlappingActors(MeleeHitboxOverlappingActors);
	for (int i = 0; i < MeleeHitboxOverlappingActors.Num(); i++) {
		if (Cast<AEntityBaseCharacter>(MeleeHitboxOverlappingActors[i])) {
			MeleeWeaponHit(MeleeHitboxOverlappingActors[i]);
		}
	}
}


bool AEntityBaseCharacter::OnInteract_Implementation()
{
	if (CurrentDialogueStage == -1) {
		Cast<ATheHazardsPlayerController>(GetWorld()->GetFirstPlayerController())->GetPawnAsEntityPlayerCharacter()->OpenDialogue();
		CurrentDialogueStage++;
	} else if (CurrentDialogueStage >= 1) {
		Cast<ATheHazardsPlayerController>(GetWorld()->GetFirstPlayerController())->GetPawnAsEntityPlayerCharacter()->OpenDialogue();
		CurrentDialogueStage = -1;
	} else {
		CurrentDialogueStage++;
	}

	return true;
}