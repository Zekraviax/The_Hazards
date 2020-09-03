#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/ScrollBox.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/UObjectGlobals.h"
#include "GameFramework/AsyncActionHandleSaveGame.h"
#include "SubWidget_SaveLoadSlot.h"

#include "BaseClass_Widget_SaveLoad.generated.h"

// Forward Declarations
class AEntity_Player;


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

// ------------------------- References
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "References")
	AEntity_Player* PlayerReference;

// Functions
// --------------------------------------------------

// ------------------------- Save Files
	UFUNCTION()
	void GetSaveFiles(bool SaveMode);
};
