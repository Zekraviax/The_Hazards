#pragma once


#include "CoreMinimal.h"

#include "Components/Button.h"
#include "Components/ScrollBox.h"
#include "Components/UniformGridPanel.h"
#include "Blueprint/UserWidget.h"
#include "TheHazardsVariables.h"

#include "WidgetMenuCraftingWindow.generated.h"


class UActorComponentInventory;
class UWidgetCraftingWindowItemScrollBox;
class UWidgetCraftingWindowItemSlot;


UCLASS()
class THEHAZARDS_API UWidgetMenuCraftingWindow : public UUserWidget
{
	GENERATED_BODY()
	

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UUniformGridPanel* CraftingSlotsGridPanel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UScrollBox* BlueprintsInventoryScrollBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UScrollBox* ComponentsInventoryScrollBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UActorComponentInventory* OwningEntityInventoryComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UWidgetCraftingWindowItemScrollBox> CraftingWindowItemScrollBoxClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UWidgetCraftingWindowItemScrollBox* CraftingWindowItemScrollBoxReference;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* CraftWeaponButton;

	FItemBase CurrentSelectedBlueprint;

	UFUNCTION()
	void PopulateScrollBoxes();

	UFUNCTION()
	void OnCraftingWindowItemSlotHoverBegin(UWidgetCraftingWindowItemSlot* HoveredItemSlot);

	UFUNCTION()
	void OnCraftingWindowItemSlotHoverEnd(UWidgetCraftingWindowItemSlot* HoveredItemSlot);

	UFUNCTION()
	void BlueprintSelected(FItemBase SelectedBlueprint);

	UFUNCTION(BlueprintCallable)
	bool ItemCraftingCheck();

	UFUNCTION(BlueprintCallable)
	void CraftItem();
};