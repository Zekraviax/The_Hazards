// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity_Player.h"

#include "BaseClass_PlayerController.h"
#include "EngineUtils.h"
#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"


// Functions
// --------------------------------------------------

// Base actor functions -------------------------

// Sets default values
AEntity_Player::AEntity_Player()
{
	// Construct actor components
	IsometricCamera = CreateDefaultSubobject<UCameraComponent>("IsometricCamera");

	// Attach components
	IsometricCamera->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AEntity_Player::BeginPlay()
{
	Super::BeginPlay();

	// Spawn the HUD widget
	if (Player_HUD_Class) {
		Player_HUD_Reference = CreateWidget<UBaseClass_Widget_PlayerHUD>(GetWorld(), Player_HUD_Class);
		Player_HUD_Reference->PlayerReference = this;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Create Widget: PlayerHUD"));
		Player_HUD_Reference->AddToViewport();
	}

	// Setup Hitbox collisions
	//BoxCollider->SetCollisionProfileName(TEXT("Trigger"));
	//BoxCollider->SetGenerateOverlapEvents(true);
	//BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &AEntity_Player::OnOverlapBegin);
	WeaponCollider->SetCollisionProfileName(TEXT("Trigger"));
	WeaponCollider->SetGenerateOverlapEvents(true);
	WeaponCollider->OnComponentBeginOverlap.AddDynamic(this, &AEntity_Player::OnOverlapBegin);

	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Entity Spawned: Entity_Player"));
}

// Called every frame
void AEntity_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Call Tick functions
	RotatePlayerTowardsMouse();

	GEngine->AddOnScreenDebugMessage(-1, 0.05f, FColor::Green, TEXT("Entity Functions: Tick Events"));
}

// Called to bind functionality to input
void AEntity_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Action Bindings
	PlayerInputComponent->BindAction("PauseGame", IE_Released, this, &AEntity_Player::OpenPauseMenu).bExecuteWhenPaused = true;

	// Movement Bindings
	PlayerInputComponent->BindAxis("MoveForwardBackward", this, &AEntity_Player::MoveForwardBackward);
	PlayerInputComponent->BindAxis("MoveLeftRight", this, &AEntity_Player::MoveLeftRight);
}

// Tick functions -------------------------
void AEntity_Player::RotatePlayerTowardsMouse()
{
	if (!LocalPlayerControllerReference)
		LocalPlayerControllerReference = Cast<ABaseClass_PlayerController>(GetWorld()->GetFirstPlayerController());
	
	FHitResult HitResult;
	FRotator LookAtRotation;

	LocalPlayerControllerReference->GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_Camera), false, HitResult);
	LookAtRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), HitResult.Location);

	PlayerRotationTowardsMouseValue = FRotator(this->GetActorRotation().Pitch, LookAtRotation.Yaw, this->GetActorRotation().Roll);
	CubeMesh->SetWorldRotation(PlayerRotationTowardsMouseValue);

	// Update the actor's forward vector to match rotation
	//RootComponent->MoveComponent(FVector::ZeroVector, PlayerRotationTowardsMouseValue, true);

	//FString RollText = FString::SanitizeFloat(PlayerRotationTowardsMouseValue.Yaw);
	//GEngine->AddOnScreenDebugMessage(-1, 0.05f, FColor::Green, TEXT("Entity Functions: Rotate Player Towards Cursor));
}

// Movement functions -------------------------
void AEntity_Player::MoveForwardBackward(float AxisValue)
{
	AddMovementInput(IsometricCamera->GetForwardVector(), AxisValue);
}

void AEntity_Player::MoveLeftRight(float AxisValue)
{
	AddMovementInput(IsometricCamera->GetRightVector(), AxisValue);
}

// Menu functions -------------------------
void AEntity_Player::OpenMutuallyExclusiveMenu()
{
	CurrentOpenMenuWidget->AddToViewport();
	UGameplayStatics::SetGamePaused(GetWorld(), true);
}

void AEntity_Player::OpenPauseMenu()
{
	if (CurrentOpenMenuWidget && CurrentOpenMenuWidget->GetClass() == PauseMenu_Class) {
		UGameplayStatics::SetGamePaused(GetWorld(), false);
		CurrentOpenMenuWidget->RemoveFromParent();
		CurrentOpenMenuWidget = NULL;
	}
	else if (!CurrentOpenMenuWidget){
		//ChosenWidgetClass = UBaseClass_Widget_PauseMenu::StaticClass();
		CurrentOpenMenuWidget = CreateWidget<UBaseClass_Widget_PauseMenu>(GetWorld(), PauseMenu_Class);

		Cast<UBaseClass_Widget_PauseMenu>(CurrentOpenMenuWidget)->LocalPlayerReference = this;
		CurrentOpenMenuWidget->AddToViewport();
		UGameplayStatics::SetGamePaused(GetWorld(), true);
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Entity Functions: OpenPauseMenu Error."));
	}
}