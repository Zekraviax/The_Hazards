#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "GameFramework/SaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "Misc/DateTime.h"

#include "SubWidget_SaveLoadSlot.generated.h"

// Forward Declarations
class USaveFile_Slot;
class UBaseClass_Widget_SaveLoad;
class USubWidget_NameSaveFile;
class USubWidget_WarningAndErrorPrompt;


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
	UTextBlock* SelectButtonText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	UTextBlock* SlotNameText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	UTextBlock* CharacterNameText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	UTextBlock* LevelText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	UTextBlock* PlaytimeText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	UTextBlock* DateSavedText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	UTextBlock* SlotNumberText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	UTextBlock* SaveCountText;

// ------------------------- Widgets
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<USubWidget_NameSaveFile> NameSaveFileWidget_Class;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widgets")
	USubWidget_NameSaveFile* NameSaveFileWidget_Reference;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<UBaseClass_Widget_SaveLoad> SaveLoadWidget_Class;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<USubWidget_WarningAndErrorPrompt> WarningAndErrorPrompt_Class;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widgets")
	USubWidget_WarningAndErrorPrompt* WarningAndErrorPrompt_Reference;

// ------------------------- Save/Load
	UPROPERTY()
	bool SaveMode;

	UPROPERTY()
	E_SaveLoadSlotFunctions SlotFunction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save/Load")
	TSubclassOf<USaveFile_Slot> SlotClass;

	UPROPERTY()
	USaveFile_Slot* SlotReference;


// Functions
// --------------------------------------------------

// ------------------------- Save/Load
	UFUNCTION(BlueprintCallable)
	void SetSlotData();

	UFUNCTION(BlueprintCallable)
	void SelectSlot();

	UFUNCTION()
	void CreateNewSaveFileSlot(FText SaveSlotName);
};
