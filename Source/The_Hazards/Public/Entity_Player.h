#pragma once

#include "CoreMinimal.h"
#include "Entity_Base.h"

#include "BaseClass_Widget_PlayerHUD.h"
#include "BaseClass_Widget_PauseMenu.h"
#include "BaseClass_Widget_Inventory.h"
#include "BaseClass_Widget_ItemCraft.h"
#include "BaseClass_Widget_CharacterSheet.h"
#include "BaseClass_Widget_CharCreator.h"
#include "BaseClass_Widget_SkillTree.h"
#include "SubWidget_StatusEffectIcon.h"

#include "Entity_Player.generated.h"

// Forward Declarations
class ABaseClass_PlayerController;
class AEntity_NPC;


// Exclusive enums
UENUM(BlueprintType)
enum class E_MenuWidgetTypes : uint8
{
	E_CharacterCreator,
	E_CharacterSheet,
	E_Inventory,
	E_SkillTree,
};

UCLASS()
class THE_HAZARDS_API AEntity_Player : public AEntity_Base
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEntity_Player();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

// Base Variables
// --------------------------------------------------

// ------------------------- Components
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UCameraComponent* IsometricCamera;

// ------------------------- Widgets
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widgets")
	UBaseClass_Widget_PlayerHUD* Player_HUD_Reference;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<UBaseClass_Widget_PlayerHUD> Player_HUD_Class;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<UBaseClass_Widget_PauseMenu> PauseMenu_Class;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<UBaseClass_Widget_Inventory> Inventory_Class;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<UBaseClass_Widget_CharacterSheet> CharacterSheet_Class;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<UBaseClass_Widget_CharCreator> CharacterCreator_Class;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<UBaseClass_Widget_SkillTree> SkillTree_Class;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<USubWidget_StatusEffectIcon> StatusEffectIcon_Class;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<UBaseClass_Widget_ItemCraft> ItemCraft_Class;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> CurrentOpenMenuWidget_Class;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widgets")
	UUserWidget* CurrentOpenMenuWidget;

// Technical Variables
// --------------------------------------------------
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Technical Variables")
	ABaseClass_PlayerController* LocalPlayerControllerReference;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Technical Variables")
	FRotator PlayerRotationTowardsMouseValue;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Technical Variables")
	TSubclassOf<UUserWidget> ChosenWidgetClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Technical Variables")
	TArray<AActor*> InteractableEntities;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Technical Variables")
	AEntity_NPC* ConversingActor;

// Functions
// --------------------------------------------------

// ------------------------- BeginPlay

// ------------------------- Tick
	UFUNCTION()
	void RotatePlayerTowardsMouse();

// ------------------------- Movement
	UFUNCTION()
	void MoveForwardBackward(float AxisValue);

	UFUNCTION()
	void MoveLeftRight(float AxisValue);

// ------------------------- Menus and Pause Screens
	//UFUNCTION()
	//void OpenMenuWidget(E_MenuWidgetTypes MenuType);

	UFUNCTION()
	void OpenPauseMenu();

	UFUNCTION()
	void OpenInventory();

	UFUNCTION()
	void OpenCharacterSheet();

	UFUNCTION()
	void OpenCharacterCreator();

	UFUNCTION()
	void OpenSkillTree();

// ------------------------- Widgets
	UFUNCTION()
	void CreateStatusEffectWidget(F_StatusEffect_Base StatusEffect);

	UFUNCTION()
	void UpdateStatusEffectWidgets();

// ------------------------- Non-Player Characters
	UFUNCTION()
	void Interact();

// ------------------------- Player
	UFUNCTION()
	void GainExperience(int ExperienceToGrant);

// ------------------------- Equipment
	UFUNCTION()
	void EquipPrimaryWeapon();

	UFUNCTION()
	void EquipSecondaryWeapon();

	UFUNCTION()
	void EquipTertiaryWeapon();

	UFUNCTION()
	F_Item_BaseStruct ReturnEquippedWeapon();
};
