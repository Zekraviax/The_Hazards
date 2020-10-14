#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

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

// ------------------------- Components
	UPROPERTY()
	AEntity_Player* PlayerReference;

// Function
// --------------------------------------------------
	
// ------------------------- Button Functions
	UFUNCTION(BlueprintCallable)
	void ChangePlayerLevel(int LevelChangeValue);
};
