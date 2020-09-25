#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/ScrollBox.h"
#include "UObject/UObjectGlobals.h"
#include "SubWidget_SaveLoadSlot.h"

#include "BaseClass_Widget_SaveLoad.generated.h"

// Forward Declarations
class AEntity_Player;
class USaveFile_MetaList;
class ABaseClass_PlayerController;
class UBaseClass_Widget_MainMenu;
class UBaseClass_Widget_PauseMenu;
class USubWidget_WarningAndErrorPrompt;


UCLASS()
class THE_HAZARDS_API UBaseClass_Widget_SaveLoad : public UUserWidget
{
	GENERATED_BODY()
	
public:
// Base Variables
// --------------------------------------------------

// ------------------------- Components
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	UImage* BackgroundImage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (BindWidget))
	UScrollBox* SaveFileScrollBox;

// ------------------------- Widgets
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<USubWidget_SaveLoadSlot> SaveLoadSlot_Class;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widgets")
	USubWidget_SaveLoadSlot* SaveLoadSlot_Reference;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<UBaseClass_Widget_PauseMenu> PauseMenu_Class;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widgets")
	UBaseClass_Widget_PauseMenu* PauseMenu_Reference;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<UBaseClass_Widget_MainMenu> MainMenu_Class;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widgets")
	UBaseClass_Widget_MainMenu* MainMenu_Reference;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<USubWidget_WarningAndErrorPrompt> WarningAndErrorPrompt_Class;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widgets")
	USubWidget_WarningAndErrorPrompt* WarningAndErrorPrompt_Reference;

// ------------------------- References
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "References")
	AEntity_Player* PlayerReference;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "References")
	ABaseClass_PlayerController* Player_Controller_Reference;

// ------------------------- Save/Load
	//UPROPERTY()
	//USaveFile_MetaList* MetaList;

	UPROPERTY()
	bool SaveMode;

// Functions
// --------------------------------------------------

// ------------------------- Save/Load
	UFUNCTION(BlueprintCallable)
	void GetSaveFilesPartOne(bool SetSaveMode);

	UFUNCTION(BlueprintCallable)
	void GetSaveFilesPartTwo();

	UFUNCTION(BlueprintCallable)
	void CloseWidget();
};
