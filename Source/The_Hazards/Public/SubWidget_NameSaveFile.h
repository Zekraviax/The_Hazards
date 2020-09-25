#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/EditableText.h"
#include "Kismet/GameplayStatics.h"

#include "SubWidget_NameSaveFile.generated.h"

// Forward Declarations
class USubWidget_SaveLoadSlot;
class USaveFile_MetaList;
class AEntity_Player;


UCLASS()
class THE_HAZARDS_API USubWidget_NameSaveFile : public UUserWidget
{
	GENERATED_BODY()
	
public:
// Base Variables
// --------------------------------------------------

// ------------------------- Components
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	UEditableText* SaveNameEntryBox;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	//UButton* SaveNameButton;

// ------------------------- References
	UPROPERTY()
	USubWidget_SaveLoadSlot* SaveLoadSlotWidget_Reference;

	UPROPERTY()
	AEntity_Player* PlayerReference;

// ------------------------- Save/Load
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Save/Load")
	//TSubclassOf<USaveFile_MetaList> MetaList_Class;

// Functions
// --------------------------------------------------
	UFUNCTION()
	void OpenWidget();

	UFUNCTION(BlueprintCallable)
	void SelectName();

	UFUNCTION(BlueprintCallable)
	void CloseWidget();
};
