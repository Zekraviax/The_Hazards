#include "Entity_Player.h"

#include "BaseClass_PlayerController.h"
#include "BaseClass_Widget_DevMenu.h"
#include "BaseClass_Widget_OnHoverDescription.h"
#include "Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Entity_NPC.h"
#include "Entity_Item.h"
#include "TheHazards_GameInstance.h"


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

	// Initialize player specific variables
	UnspentSkillPoints = 3;
	Money = 1000;
	Experience = 95;
	LockMenuButtonActions = false;
}


// Called when the game starts or when spawned
void AEntity_Player::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void AEntity_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Call Tick functions
	RotatePlayerTowardsMouse();

	if (GetWorldTimerManager().IsTimerActive(ClearLoadingScreenTimerHandle)) {
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, FString::Printf(TEXT("Message: ClearLoadingScreenTimer time: %s"), GetWorldTimerManager().GetTimerElapsed(ClearLoadingScreenTimerHandle)));
	}
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
	PlayerInputComponent->BindAction("OpenItemCraft", IE_Released, this, &AEntity_Player::OpenItemCraftMenu).bExecuteWhenPaused = true;

	// Attacks
	PlayerInputComponent->BindAction("PrimaryAttack", IE_Released, this, &AEntity_Player::AttackStart);
	PlayerInputComponent->BindAction("SpecialAttack", IE_Released, this, &AEntity_Player::SpecialAttackStart);

	// Other
	PlayerInputComponent->BindAction("Interact", IE_Released, this, &AEntity_Player::Interact);
	PlayerInputComponent->BindAction("EquipPrimaryWeapon", IE_Released, this, &AEntity_Player::EquipPrimaryWeapon);
	PlayerInputComponent->BindAction("EquipSecondaryWeapon", IE_Released, this, &AEntity_Player::EquipSecondaryWeapon);
	PlayerInputComponent->BindAction("EquipTertiaryWeapon", IE_Released, this, &AEntity_Player::EquipTertiaryWeapon);

	// Movement 
	PlayerInputComponent->BindAxis("MoveForward", this, &AEntity_Player::MoveForwardBackward);
	PlayerInputComponent->BindAxis("MoveBackward", this, &AEntity_Player::MoveForwardBackward);
	PlayerInputComponent->BindAxis("MoveLeft", this, &AEntity_Player::MoveLeftRight);
	PlayerInputComponent->BindAxis("MoveRight", this, &AEntity_Player::MoveLeftRight);
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AEntity_Player::Sprint);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AEntity_Player::Sprint);
	PlayerInputComponent->BindAction("Sneak", IE_Pressed, this, &AEntity_Player::Sneak);
	PlayerInputComponent->BindAction("Sneak", IE_Released, this, &AEntity_Player::Sneak);
	PlayerInputComponent->BindAction("Dodge", IE_Pressed, this, &AEntity_Player::Dodge);
}


// ------------------------- BeginPlay
void AEntity_Player::ManualBeginPlay()
{
	// Spawn the HUD widget
	if (Player_HUD_Class) {
		Player_HUD_Reference = CreateWidget<UBaseClass_Widget_PlayerHUD>(GetWorld(), Player_HUD_Class);

		if (Player_HUD_Reference->IsValidLowLevel()) {
			Player_HUD_Reference->PlayerReference = this;
			Player_HUD_Reference->AddToViewport();
		}
	}
}


//  ------------------------- Tick
void AEntity_Player::RotatePlayerTowardsMouse()
{
	FHitResult HitResult;
	FRotator LookAtRotation;

	if (!Player_Controller_Reference)
		Player_Controller_Reference = Cast<ABaseClass_PlayerController>(GetWorld()->GetFirstPlayerController());
	else {
		if (Player_Controller_Reference->GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_Camera), false, HitResult)) {
			LookAtRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), HitResult.Location);

			PlayerRotationTowardsMouseValue = FRotator(this->GetActorRotation().Pitch, LookAtRotation.Yaw, this->GetActorRotation().Roll);
			CubeMesh->SetWorldRotation(PlayerRotationTowardsMouseValue);
		}
	}
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
	if (!Player_Controller_Reference && GetWorld()) {
		Player_Controller_Reference = Cast<ABaseClass_PlayerController>(GetWorld()->GetFirstPlayerController());
	}

	// Close pause menu widget and resume game
	if (Player_Controller_Reference->CurrentOpenMenuWidget_Class == PauseMenu_Class) {
		//GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, FString::Printf(TEXT("Close PauseMenu and resume Game")));
		UGameplayStatics::SetGamePaused(GetWorld(), false);

		Player_Controller_Reference->CurrentOpenMenuWidget->RemoveFromParent();
		Player_Controller_Reference->CurrentOpenMenuWidget = NULL;
		Player_Controller_Reference->CurrentOpenMenuWidget_Class = NULL;
	}
	// Create options menu widget and add to viewport
	else if (Player_Controller_Reference->CurrentOpenMenuWidget_Class == AudioMenu_Class ||
		Player_Controller_Reference->CurrentOpenMenuWidget_Class == GraphicsMenu_Class ||
		Player_Controller_Reference->CurrentOpenMenuWidget_Class == KeybindsMenu_Class ||
		Player_Controller_Reference->CurrentOpenMenuWidget_Class == ControlsMenu_Class) {

		//GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, FString::Printf(TEXT("Close Options SubMenu and open OptionsMenu")));
		Player_Controller_Reference->CurrentOpenMenuWidget->RemoveFromParent();
		Player_Controller_Reference->CurrentOpenMenuWidget = NULL;
		Player_Controller_Reference->CurrentOpenMenuWidget_Class = NULL;

		Player_Controller_Reference->CurrentOpenMenuWidget = CreateWidget<UBaseClass_Widget_Options>(GetWorld(), OptionsMenu_Class);
		//Cast<UBaseClass_Widget_Options>(CurrentOpenMenuWidget)->PlayerReference = this;
		Player_Controller_Reference->CurrentOpenMenuWidget->AddToViewport();
		Player_Controller_Reference->CurrentOpenMenuWidget_Class = OptionsMenu_Class;
	}
	else if (CurrentOpenMenuWidget_Class == OptionsMenu_Class) {
		//GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, FString::Printf(TEXT("Close OptionsMenu and open PauseMenu")));

		Cast<UBaseClass_Widget_Options>(Player_Controller_Reference->CurrentOpenMenuWidget)->CloseMenu();
	}
	// Create pause menu widget, add to viewport, and pause game
	else {
		//GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, FString::Printf(TEXT("Pause Game and open PauseMenu")));
		// Remove other widgets from screen
		if (Player_Controller_Reference->CurrentOpenMenuWidget) {
			Player_Controller_Reference->CurrentOpenMenuWidget->RemoveFromParent();
			Player_Controller_Reference->CurrentOpenMenuWidget = NULL;
		}
		if (Player_Controller_Reference->CurrentOpenMenuWidget_Class) {
			Player_Controller_Reference->CurrentOpenMenuWidget_Class = NULL;
		}

		Player_Controller_Reference->CurrentOpenMenuWidget = CreateWidget<UBaseClass_Widget_PauseMenu>(GetWorld(), PauseMenu_Class);
		Player_Controller_Reference->CurrentOpenMenuWidget_Class = Player_Controller_Reference->CurrentOpenMenuWidget->GetClass();
		Cast<UBaseClass_Widget_PauseMenu>(Player_Controller_Reference->CurrentOpenMenuWidget)->LocalPlayerReference = this;

		Player_Controller_Reference->CurrentOpenMenuWidget->AddToViewport();

		UGameplayStatics::SetGamePaused(GetWorld(), true);
	}
}


void AEntity_Player::OpenInventory()
{
	if (!LockMenuButtonActions) {
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

			// Inventory specific variables and functions
			Cast<UBaseClass_Widget_Inventory>(CurrentOpenMenuWidget)->PlayerReference = this;
			Cast<UBaseClass_Widget_Inventory>(CurrentOpenMenuWidget)->OnInventoryOpened();
			Cast<UBaseClass_Widget_Inventory>(CurrentOpenMenuWidget)->PopulateInventorySlots();

			CurrentOpenMenuWidget->AddToViewport();
			UGameplayStatics::SetGamePaused(GetWorld(), true);
		}
		else {
			CurrentOpenMenuWidget_Class = NULL;
		}
	}
}


void AEntity_Player::OpenCharacterSheet()
{
	if (!LockMenuButtonActions) {
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
}


void AEntity_Player::OpenCharacterCreator()
{
	if (!LockMenuButtonActions) {
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
}


void AEntity_Player::OpenSkillTree()
{
	if (!LockMenuButtonActions) {
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
}


void AEntity_Player::OpenItemCraftMenu()
{
	if (!LockMenuButtonActions) {
		if (CurrentOpenMenuWidget) {
			// Close widget and resume game
			UGameplayStatics::SetGamePaused(GetWorld(), false);
			CurrentOpenMenuWidget->RemoveFromParent();
			CurrentOpenMenuWidget = NULL;
		}

		if (ItemCraft_Class && CurrentOpenMenuWidget_Class != ItemCraft_Class) {
			// Create widget, add to viewport, and pause game
			CurrentOpenMenuWidget = CreateWidget<UBaseClass_Widget_ItemCraft>(GetWorld(), ItemCraft_Class);
			CurrentOpenMenuWidget_Class = ItemCraft_Class;
			UGameplayStatics::SetGamePaused(GetWorld(), true);

			// Item Craft specific variables and functions
			Cast<UBaseClass_Widget_ItemCraft>(CurrentOpenMenuWidget)->PlayerReference = this;
			Cast<UBaseClass_Widget_ItemCraft>(CurrentOpenMenuWidget)->GetPlayerInventory();

			CurrentOpenMenuWidget->AddToViewport();
		}
		else {
			CurrentOpenMenuWidget_Class = NULL;
		}
	}
}


void AEntity_Player::OpenMainMenu()
{
	if (MainMenu_Class) {
		CurrentOpenMenuWidget = CreateWidget<UBaseClass_Widget_MainMenu>(GetWorld(), MainMenu_Class);
		CurrentOpenMenuWidget->AddToViewport();
		CurrentOpenMenuWidget = NULL;
	}
}


//void AEntity_Player::OpenMenuWidget(E_MenuWidgetTypes MenuType)
//{
//	Widget MenuClass;
//	TSubclassOf<UUserWidget> MenuSubClass;
//
//	switch (MenuType) 
//	{
//	case(E_MenuWidgetTypes::E_CharacterCreator):
//		MenuClass = UBaseClass_Widget_CharacterSheet;
//		break;
//	}
//
//	CurrentOpenMenuWidget = CreateWidget<MenuClass>(GetWorld(), MenuSubClass);
//}


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


void AEntity_Player::ClearLoadingScreenTimer()
{
	GetWorldTimerManager().SetTimer(ClearLoadingScreenTimerHandle, this, &AEntity_Player::ClearLoadingScreenExecute, 2.5f, false);

	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, FString::Printf(TEXT("Message: Call ClearLoadingScreenTimer()")));
	UE_LOG(LogTemp, Display, TEXT("Message: Call ClearLoadingScreenTimer()"));

	//if (GetWorldTimerManager().IsTimerActive(ClearLoadingScreenTimerHandle)) {
	//	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, FString::Printf(TEXT("Message: ClearLoadingScreenTimer is active.")));
	//	UE_LOG(LogTemp, Display, TEXT("Message: ClearLoadingScreenTimer is active."));
	//}
	//else {
	//	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Error: ClearLoadingScreenTimer is not active.")));
	//	UE_LOG(LogTemp, Error, TEXT("Message: ClearLoadingScreenTimer is not active."));
	//}
}


void AEntity_Player::ClearLoadingScreenExecute()
{
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, FString::Printf(TEXT("Message: Call ClearLoadingScreenExecute()")));
	UE_LOG(LogTemp, Display, TEXT("Message: Call ClearLoadingScreenExecute()"));

	//Cast<UTheHazards_GameInstance>(GetWorld()->GetGameInstance())->LoadSaveFilePartFour();
}


// ------------------------- Non-Player Characters
void AEntity_Player::Interact()
{
	if (ConversingActor) {
		ConversingActor->PlayerInteract(this);
	} else {
		if (InteractableEntities.IsValidIndex(0)) {
			if (Cast<AEntity_NPC>(InteractableEntities[0])) {
				Cast<AEntity_NPC>(InteractableEntities[0])->PlayerInteract(this);
				ConversingActor = Cast<AEntity_NPC>(InteractableEntities[0]);
			}
			else if (Cast<AEntity_Item>(InteractableEntities[0])) {
				Cast<AEntity_Item>(InteractableEntities[0])->OnPlayerInteract(this);
			}
		}
	}
}


// ------------------------- Player
void AEntity_Player::GainExperience(int ExperienceToGrant)
{
	Experience += ExperienceToGrant;

	if (Experience >= (Level * 100)) {
		Experience -= (Level * 100);
		Level++;
		GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Yellow, FString::Printf(TEXT("Level Up!")));
	}
}


// ------------------------- Equipment
void AEntity_Player::EquipPrimaryWeapon()
{
	CurrentEquippedWeapon = PrimaryWeapon;
}


void AEntity_Player::EquipSecondaryWeapon()
{
	CurrentEquippedWeapon = SecondaryWeapon;
}


void AEntity_Player::EquipTertiaryWeapon()
{
	CurrentEquippedWeapon = TertiaryWeapon;
}


F_Item_BaseStruct AEntity_Player::ReturnEquippedWeapon()
{
	F_Item_BaseStruct ReturnWeapon;

	switch (CurrentEquippedWeapon.Weapon.EquipSlot)
	{
		case(E_Weapon_EquipSlot::E_Primary):
			ReturnWeapon = PrimaryWeapon;
			break;
		case(E_Weapon_EquipSlot::E_Secondary):
			ReturnWeapon = SecondaryWeapon;
			break;
		case(E_Weapon_EquipSlot::E_Tertiary):
			ReturnWeapon = TertiaryWeapon;
			break;
		default:
			ReturnWeapon = PrimaryWeapon;
			break;
	}
	return ReturnWeapon;
}
