#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/TextBlock.h"
#include "Components/Button.h"

#include "SubWidget_SaveLoadSlot.generated.h"

// Forward Declarations
class USaveFile_Slot;


// Exclusive enum
UENUM(BlueprintType)
enum class E_SaveLoadSlotFunctions : uint8
{
	E_SaveNewSlot,
	E_SaveExistingSlot,
	E_LoadExistingSLot
};


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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	UTextBlock* SlotNameText;

// ------------------------- Save/Load
	UPROPERTY()
	bool SaveMode;

	UPROPERTY()
	E_SaveLoadSlotFunctions SlotFunction;

	UPROPERTY()
	USaveFile_Slot* SlotData;

// Functions
// --------------------------------------------------

// ------------------------- Save/Load
	UFUNCTION(BlueprintCallable)
	void SetSlotData();

	UFUNCTION(BlueprintCallable)
	void SelectSlot();
};
