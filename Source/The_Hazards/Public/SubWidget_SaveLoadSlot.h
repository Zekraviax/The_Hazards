#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/TextBlock.h"
#include "Components/Button.h"

#include "SubWidget_SaveLoadSlot.generated.h"


UCLASS()
class THE_HAZARDS_API USubWidget_SaveLoadSlot : public UUserWidget
{
	GENERATED_BODY()

public:
// Base Variables
// --------------------------------------------------

// ------------------------- Components
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	UButton* SelectButton;

// ------------------------- Save/Load
	UPROPERTY()
	bool SaveMode;

// Functions
// --------------------------------------------------

// ------------------------- Save/Load
	UFUNCTION(BlueprintCallable)
	void SelectSlot();
};
