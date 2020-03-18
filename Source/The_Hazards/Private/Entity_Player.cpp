// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity_Player.h"

#include "BaseClass_PlayerController.h"
#include "BaseClass_Widget_OnHoverDescription.h"
#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Entity_NPC.h"


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
	Money = 9999999;
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
			TArray<FName> RowNames = SkillsFunctionLibrary_Reference->SkillDataTable_Reference->GetRowNames();

			for (auto& Row : SkillsFunctionLibrary_Reference->SkillDataTable_Reference->GetRowMap()) {
				F_Skill_Base* Skill = (F_Skill_Base*)(Row.Value);

				//if (Skill->SkillIndex == 101) {
				//	Skill->CurrentLevel += 1;
				//}

				KnownSkills.Add(*Skill);
			}

			CalculateTotalStats();
		}
	}
}

// Called every frame
void AEntity_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//GEngine->AddOnScreenDebugMessage(-1, DeltaTime, FColor::Black, TEXT("Player Tick"));

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
	PlayerInputComponent->BindAction("OpenCharacterSheet", IE_Released, this, &AEntity_Player::OpenCharacterSheet).bExecuteWhenPaused = true;
	PlayerInputComponent->BindAction("OpenCharacterCreator", IE_Released, this, &AEntity_Player::OpenCharacterCreator).bExecuteWhenPaused = true;
	PlayerInputComponent->BindAction("OpenSkillTree", IE_Released, this, &AEntity_Player::OpenSkillTree).bExecuteWhenPaused = true;

	// Attacks
	PlayerInputComponent->BindAction("PrimaryAttack", IE_Released, this, &AEntity_Player::AttackStart);

	// Other
	PlayerInputComponent->BindAction("Interact", IE_Released, this, &AEntity_Player::Interact);

	// Movement 
	PlayerInputComponent->BindAxis("MoveForwardBackward", this, &AEntity_Player::MoveForwardBackward);
	PlayerInputComponent->BindAxis("MoveLeftRight", this, &AEntity_Player::MoveLeftRight);
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AEntity_Player::Sprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AEntity_Player::Sprint);
	PlayerInputComponent->BindAction("Sneak", IE_Pressed, this, &AEntity_Player::Sneak);
	PlayerInputComponent->BindAction("Sneak", IE_Released, this, &AEntity_Player::Sneak);
	PlayerInputComponent->BindAction("Dodge", IE_Pressed, this, &AEntity_Player::Dodge);
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
		//Close widget and resume game
		UGameplayStatics::SetGamePaused(GetWorld(), false);

		// Remove OnHoverDescription widgets
		for (TObjectIterator<UBaseClass_Widget_OnHoverDescription> Itr; Itr; ++Itr) {
			UBaseClass_Widget_OnHoverDescription *FoundWidget = *Itr;
			FoundWidget->RemoveFromParent();
		}

		CurrentOpenMenuWidget->RemoveFromParent();
		CurrentOpenMenuWidget = NULL;
	}

	if (Inventory_Class && CurrentOpenMenuWidget_Class != Inventory_Class) {
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

	if (CharacterCreator_Class && CurrentOpenMenuWidget_Class != CharacterCreator_Class) {
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
		//Close widget and resume game
		UGameplayStatics::SetGamePaused(GetWorld(), false);

		// Remove OnHoverDescription widgets
		for (TObjectIterator<UBaseClass_Widget_OnHoverDescription> Itr; Itr; ++Itr) {
			UBaseClass_Widget_OnHoverDescription *FoundWidget = *Itr;
			FoundWidget->RemoveFromParent();
		}

		CurrentOpenMenuWidget->RemoveFromParent();
		CurrentOpenMenuWidget = NULL;
	}

	if (SkillTree_Class && CurrentOpenMenuWidget_Class != SkillTree_Class) {
		// Create widget, add to viewport, and pause game
		CurrentOpenMenuWidget = CreateWidget<UBaseClass_Widget_SkillTree>(GetWorld(), SkillTree_Class);
		CurrentOpenMenuWidget_Class = SkillTree_Class;
		CurrentOpenMenuWidget->AddToViewport();
		UGameplayStatics::SetGamePaused(GetWorld(), true);

		// Inventory specific variables and functions
		Cast<UBaseClass_Widget_SkillTree>(CurrentOpenMenuWidget)->PlayerReference = this;
		Cast<UBaseClass_Widget_SkillTree>(CurrentOpenMenuWidget)->UpdateAllSkillSlots();
	}
	else {
		CurrentOpenMenuWidget_Class = NULL;
	}
}

void AEntity_Player::OpenMenuWidget(E_MenuWidgetTypes MenuType)
{
	//Widget MenuClass;
	//TSubclassOf<UUserWidget> MenuSubClass;

	//switch (MenuType) 
	//{
	//case(E_MenuWidgetTypes::E_CharacterCreator):
	//	MenuClass = UBaseClass_Widget_CharacterSheet;
	//	break;
	//}

	//CurrentOpenMenuWidget = CreateWidget<MenuClass>(GetWorld(), MenuSubClass);
}
// ------------------------- HUD
void AEntity_Player::CreateStatusEffectWidget(F_StatusEffect_Base StatusEffect)
{
	if (Player_HUD_Reference->StatusEffects_ScrollBox->IsValidLowLevel()) {
		USubWidget_StatusEffectIcon* StatusEffectIcon = CreateWidget<USubWidget_StatusEffectIcon>(GetWorld(), StatusEffectIcon_Class);
		StatusEffectIcon->UpdateStatusEffectData(StatusEffect);
		StatusEffectIcon->StatusEffectIcon->SetBrushFromTexture(StatusEffect.StatusEffectImage, true);
		Player_HUD_Reference->StatusEffects_ScrollBox->AddChild(StatusEffectIcon);

		//GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Orange, FString::Printf(TEXT("Update Status Effects: %d"), Player_HUD_Reference->StatusEffects_ScrollBox->GetChildrenCount()));
	}
}

void AEntity_Player::UpdateStatusEffectWidgets()
{
	// Tick Status Effect Widgets
	for (int i = 0; i < StatusEffectsArray.Num(); i++) {
		for (int j = 0; j < Player_HUD_Reference->StatusEffects_ScrollBox->GetChildrenCount(); j++) {
			if (j == i) {
				Cast<USubWidget_StatusEffectIcon>(Player_HUD_Reference->StatusEffects_ScrollBox->GetChildAt(j))->UpdateStatusEffectData(StatusEffectsArray[i]);

				if (Cast<USubWidget_StatusEffectIcon>(Player_HUD_Reference->StatusEffects_ScrollBox->GetChildAt(j))->StatusEffectData.CurrentStackCount <= 0) {
					Player_HUD_Reference->StatusEffects_ScrollBox->RemoveChildAt(i);
				}
			}
		}
	}
}

// ------------------------- Non-Player Characters
void AEntity_Player::Interact()
{
	// Sphere trace for interactable NPCs
	FHitResult HitResult;
	TArray<FHitResult> HitResults;
	FVector Location = this->GetActorLocation();
	ECollisionChannel TraceChannel = ECollisionChannel::ECC_GameTraceChannel1;
	FCollisionShape SphereShape = FCollisionShape::MakeSphere(200.f);

	DrawDebugSphere(GetWorld(), Location, SphereShape.GetSphereRadius(), 50, FColor::Red, false, 2.5f);
	GetWorld()->SweepMultiByChannel(HitResults, Location, FVector(Location.X, Location.Y, Location.Z + 0.01), FQuat(0, 0, 0, 0), TraceChannel, SphereShape);

	for (int i = 0; i < HitResults.Num(); i++) {
		if (HitResults[i].GetActor()->IsA(AEntity_NPC::StaticClass())) {
			Cast<AEntity_NPC>(HitResults[i].GetActor())->PlayerInteract();
			break;
		}
	}
}

// ------------------------- Attacks