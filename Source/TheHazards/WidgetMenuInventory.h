#pragma once


#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"
#include "Components/ScrollBox.h"
#include "Components/UniformGridPanel.h"

#include "WidgetMenuInventory.generated.h"


class UActorComponentInventory;
class UWidgetInventoryListItem;


UCLASS()
class THEHAZARDS_API UWidgetMenuInventory : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UUniformGridPanel* UnequippedInventoryItemsGridPanel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UUniformGridPanel* EquippedInventoryItemsGridPanel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UWidgetInventoryListItem> InventoryListItemClass;

	// To-Do: Document this
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UWidgetInventoryListItem* InventoryListItemReference;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UActorComponentInventory* OwningEntityInventoryComponent;

	// Consumable item slot
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UWidgetInventoryListItem* InventoryListItem_QuickUseItem1;

	UFUNCTION(BlueprintCallable)
	void PopulateUnequippedItemsScrollBox(UActorComponentInventory* Inventory);

	UFUNCTION(BlueprintCallable)
	void PopulateEquippedItemsScrollBox(UActorComponentInventory* Inventory);

	void RefreshOtherSlots(UActorComponentInventory* Inventory);

	void OnCursorBeginOverItemSlot();
	void OnCursorEndOverItemSlot();

	// For the item widgets
	void SwapItemsBetweenSlots(UWidgetInventoryListItem* ItemSlotOne, UWidgetInventoryListItem* ItemSlotTwo);
};
