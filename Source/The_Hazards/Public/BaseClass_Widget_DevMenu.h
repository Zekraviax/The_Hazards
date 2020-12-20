#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/ComboBoxString.h"

#include "BaseClass_Widget_DevMenu.generated.h"

// Forward Declarations
class AEntity_Base;


UCLASS()
class THE_HAZARDS_API UBaseClass_Widget_DevMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:
// Base Variables
// --------------------------------------------------

// ------------------------- Components
	//UPROPERTY(meta = (BindWidget))
	//UButton* IncreaseLevelButton;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* PlayerLevelText;

	UPROPERTY(meta = (BindWidget))
	UComboBoxString* SwitchLevel_DropDown;

// ------------------------- References
	UPROPERTY()
	AEntity_Player* PlayerReference;

// Function
// --------------------------------------------------

// ------------------------- Widget
	UFUNCTION()
	void OpenWidget();

	UFUNCTION()
	void UpdateVariables();
	
// ------------------------- Functions
	UFUNCTION(BlueprintCallable)
	void ChangePlayerLevel(int LevelChangeValue);

	UFUNCTION(BlueprintCallable)
	void OnSwitchLevelDropdownChanged();

	UFUNCTION()
	void LoadNewLevel();
};
