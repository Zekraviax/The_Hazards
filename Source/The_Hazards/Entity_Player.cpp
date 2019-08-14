// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity_Player.h"

#include "BaseClass_PlayerController.h"
#include "EngineUtils.h"
#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"


// Functions
// --------------------------------------------------

// ------------------------- Base actor functions 

// Sets default values
AEntity_Player::AEntity_Player()
{
	// Construct actor components
	IsometricCamera = CreateDefaultSubobject<UCameraComponent>("IsometricCamera");

	// Attach components
	IsometricCamera->SetupAttachment(RootComponent);

	// Initialize variables
	UnspentSkillPoints = 3;
}

// Called when the game starts or when spawned
void AEntity_Player::BeginPlay()
{
	Super::BeginPlay();

	// Spawn the HUD widget
	if (Player_HUD_Class) {
		Player_HUD_Reference = CreateWidget<UBaseClass_Widget_PlayerHUD>(GetWorld(), Player_HUD_Class);
		Player_HUD_Reference->PlayerReference = this;
		Player_HUD_Reference->AddToViewport();
	}

	// Setup Hitbox collisions
	WeaponCollider->SetCollisionProfileName(TEXT("Trigger"));
	WeaponCollider->SetGenerateOverlapEvents(false);
	WeaponCollider->OnComponentBeginOverlap.AddDynamic(this, &AEntity_Player::OnOverlapBegin);

	// Setup Skill Tree
	if (SkillsFunctionLibrary_Reference) {
		if (SkillsFunctionLibrary_Reference->SkillDataTable_Reference) {
			FString ContextString;
			F_Skill_Base* ElementBaseSkill;

			for (FName Name : SkillsFunctionLibrary_Reference->SkillDataTable_Reference->GetRowNames()) {
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, TEXT("Skill: " + Name.ToString()));
				ElementBaseSkill = SkillsFunctionLibrary_Reference->SkillDataTable_Reference->FindRow<F_Skill_Base>(Name, ContextString, true);
				if (ElementBaseSkill) {
					//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, TEXT("Get Aer Skill"));
					ElementBaseSkill->CurrentLevel = 1;
					KnownSkills.Add(*ElementBaseSkill);
				}
				//else {
				//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Purple, TEXT("Skill Error"));
				//}
			}
		}
	}
}

// Called every frame
void AEntity_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Call Tick functions
	RotatePlayerTowardsMouse();
}

// Called to bind functionality to input
void AEntity_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Action Bindings
	// Menus
	PlayerInputComponent->BindAction("PauseGame", IE_Released, this, &AEntity_Player::OpenPauseMenu).bExecuteWhenPaused = true;
	PlayerInputComponent->BindAction("OpenInventory", IE_Released, this, &AEntity_Player::OpenInventory).bExecuteWhenPaused = true;
	PlayerInputComponent->BindAction("OpenSkillTree", IE_Released, this, &AEntity_Player::OpenSkillTree).bExecuteWhenPaused = true;
	PlayerInputComponent->BindAction("OpenCharacterSheet", IE_Released, this, &AEntity_Player::OpenCharacterSheet).bExecuteWhenPaused = true;
	PlayerInputComponent->BindAction("OpenCharacterCreator", IE_Released, this, &AEntity_Player::OpenCharacterCreator).bExecuteWhenPaused = true;

	// Attacks
	PlayerInputComponent->BindAction("PrimaryAttack", IE_Released, this, &AEntity_Player::AttackStart);

	// Movement Bindings
	PlayerInputComponent->BindAxis("MoveForwardBackward", this, &AEntity_Player::MoveForwardBackward);
	PlayerInputComponent->BindAxis("MoveLeftRight", this, &AEntity_Player::MoveLeftRight);
}

//  ------------------------- Tick
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
}

// ------------------------- Movement
void AEntity_Player::MoveForwardBackward(float AxisValue)
{
	AddMovementInput(IsometricCamera->GetForwardVector(), AxisValue);
}

void AEntity_Player::MoveLeftRight(float AxisValue)
{
	AddMovementInput(IsometricCamera->GetRightVector(), AxisValue);
}

// ------------------------- Menu and Pause Screens
void AEntity_Player::OpenPauseMenu()
{
	if (CurrentOpenMenuWidget) {
		// Close widget and resume game
		UGameplayStatics::SetGamePaused(GetWorld(), false);
		CurrentOpenMenuWidget->RemoveFromParent();
		CurrentOpenMenuWidget = NULL;
	}
	else if (!CurrentOpenMenuWidget && PauseMenu_Class) {
		// Create widget, add to viewport, and pause game
		CurrentOpenMenuWidget = CreateWidget<UBaseClass_Widget_PauseMenu>(GetWorld(), PauseMenu_Class);

		Cast<UBaseClass_Widget_PauseMenu>(CurrentOpenMenuWidget)->LocalPlayerReference = this;
		CurrentOpenMenuWidget->AddToViewport();
		UGameplayStatics::SetGamePaused(GetWorld(), true);
	}
}

void AEntity_Player::OpenInventory()
{
	if (CurrentOpenMenuWidget) {
		// Close widget and resume game
		UGameplayStatics::SetGamePaused(GetWorld(), false);
		CurrentOpenMenuWidget->RemoveFromParent();
		CurrentOpenMenuWidget = NULL;
	}

	if (CharacterSheet_Class && CurrentOpenMenuWidget_Class != Inventory_Class) {
		// Create widget, add to viewport, and pause game
		CurrentOpenMenuWidget = CreateWidget<UBaseClass_Widget_Inventory>(GetWorld(), Inventory_Class);
		CurrentOpenMenuWidget_Class = Inventory_Class;
		CurrentOpenMenuWidget->AddToViewport();
		UGameplayStatics::SetGamePaused(GetWorld(), true);

		// Inventory specific variables and functions
		Cast<UBaseClass_Widget_Inventory>(CurrentOpenMenuWidget)->PlayerReference = this;
		Cast<UBaseClass_Widget_Inventory>(CurrentOpenMenuWidget)->PopulateInventorySlots();
	}
	else {
		CurrentOpenMenuWidget_Class = NULL;
	}
}

void AEntity_Player::OpenCharacterSheet()
{
	if (CurrentOpenMenuWidget) {
		// Close widget and resume game
		UGameplayStatics::SetGamePaused(GetWorld(), false);
		CurrentOpenMenuWidget->RemoveFromParent();
		CurrentOpenMenuWidget = NULL;
	}

	if (CharacterSheet_Class && CurrentOpenMenuWidget_Class != CharacterSheet_Class) {
		// Create widget, add to viewport, and pause game
		CurrentOpenMenuWidget = CreateWidget<UBaseClass_Widget_CharacterSheet>(GetWorld(), CharacterSheet_Class);
		CurrentOpenMenuWidget_Class = CharacterSheet_Class;
		CurrentOpenMenuWidget->AddToViewport();
		UGameplayStatics::SetGamePaused(GetWorld(), true);

		// Character Sheet specific variables and functions
		Cast<UBaseClass_Widget_CharacterSheet>(CurrentOpenMenuWidget)->PlayerReference = this;
		Cast<UBaseClass_Widget_CharacterSheet>(CurrentOpenMenuWidget)->OpenCharacterSheet();
	}
	else {
		CurrentOpenMenuWidget_Class = NULL;
	}
}

void AEntity_Player::OpenCharacterCreator()
{
	if (CurrentOpenMenuWidget) {
		// Close widget and resume game
		UGameplayStatics::SetGamePaused(GetWorld(), false);
		CurrentOpenMenuWidget->RemoveFromParent();
		CurrentOpenMenuWidget = NULL;
	}

	if (CharacterSheet_Class && CurrentOpenMenuWidget_Class != CharacterCreator_Class) {
		// Create widget, add to viewport, and pause game
		CurrentOpenMenuWidget = CreateWidget<UBaseClass_Widget_CharCreator>(GetWorld(), CharacterCreator_Class);
		CurrentOpenMenuWidget_Class = CharacterCreator_Class;
		CurrentOpenMenuWidget->AddToViewport();
		UGameplayStatics::SetGamePaused(GetWorld(), true);

		// Character Creator specific variables and functions
		Cast<UBaseClass_Widget_CharCreator>(CurrentOpenMenuWidget)->PlayerReference = this;
	}
	else {
		CurrentOpenMenuWidget_Class = NULL;
	}
}

void AEntity_Player::OpenSkillTree()
{
	if (CurrentOpenMenuWidget) {
		// Close widget and resume game
		UGameplayStatics::SetGamePaused(GetWorld(), false);
		CurrentOpenMenuWidget->RemoveFromParent();
		CurrentOpenMenuWidget = NULL;
	}

	if (CharacterSheet_Class && CurrentOpenMenuWidget_Class != SkillTree_Class) {
		// Create widget, add to viewport, and pause game
		CurrentOpenMenuWidget = CreateWidget<UBaseClass_Widget_SkillTree>(GetWorld(), SkillTree_Class);
		CurrentOpenMenuWidget_Class = SkillTree_Class;
		CurrentOpenMenuWidget->AddToViewport();
		UGameplayStatics::SetGamePaused(GetWorld(), true);

		// Skill Tree specific variables and functions
		Cast<UBaseClass_Widget_SkillTree>(CurrentOpenMenuWidget)->PlayerReference = this;
		Cast<UBaseClass_Widget_SkillTree>(CurrentOpenMenuWidget)->UpdateAllSkillSlots();
	}
	else {
		CurrentOpenMenuWidget_Class = NULL;
	}
}

// ------------------------- Attacks