#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Runtime/UMG/Public/Blueprint/WidgetTree.h"
#include "SubWidget_InventorySlot.h"
#include "TheHazards_GameMode.h"

#include "BaseClass_Widget_Inventory.generated.h"

// Forward Declarations
class AEntity_Base;


UCLASS()
class THE_HAZARDS_API UBaseClass_Widget_Inventory : public UUserWidget
{
	GENERATED_BODY()

public:
// Base Variables
// --------------------------------------------------

// ------------------------- Components
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	UImage* BackgroundImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	UTextBlock* MoneyText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	UTextBlock* ScrapText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TArray<USubWidget_InventorySlot*> InventorySlotsArray;

// ------------------------- Player-related Variables
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player-Related")
	AEntity_Base* PlayerReference;

// Functions
// --------------------------------------------------
	UFUNCTION(BlueprintCallable)
	void OnInventoryOpened();

	UFUNCTION()
	void PopulateInventorySlots();

	UFUNCTION(BlueprintCallable)
	void OnMouseUp();
};
