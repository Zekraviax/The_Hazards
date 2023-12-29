#include "WidgetItemRightClickMenu.h"


#include "ActorComponentInventory.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "TheHazardsVariables.h"
#include "WidgetInventoryListItem.h"
#include "WidgetMenuInventory.h"


void UWidgetItemRightClickMenu::ShowHideEquipUnequipButtons(bool ShowEquipButton)
{
	// One of the Equip and Unequip buttons should be shown
	// and the other hidden at all times
	if (ShowEquipButton) {
		EquipButton->SetVisibility(ESlateVisibility::Visible);
		UnequipButton->SetVisibility(ESlateVisibility::Collapsed);
	} else {
		EquipButton->SetVisibility(ESlateVisibility::Collapsed);
		UnequipButton->SetVisibility(ESlateVisibility::Visible);
	}
}


void UWidgetItemRightClickMenu::EquipButtonPressed()
{
	// Get the item the player clicked 'equip' for
	FItemBase SelectedItem = ClickedWidgetInventoryListItem->ItemReference;

	// Get the currently equipped item
	FItemBase EquippedItem;
	UWidgetInventoryListItem* FoundInventoryListItem = nullptr;

	TArray<UUserWidget*> FoundInventoryItemWidgets;
	UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), FoundInventoryItemWidgets, UWidgetInventoryListItem::StaticClass(), false);

	if (SelectedItem.EquipSlot != EItemSlotTypes::None) {
		for (int i = 0; i < FoundInventoryItemWidgets.Num(); i++) {
			FoundInventoryListItem = Cast<UWidgetInventoryListItem>(FoundInventoryItemWidgets[i]);

			if (FoundInventoryListItem->ItemSlot == SelectedItem.EquipSlot) {
				EquippedItem = FoundInventoryListItem->ItemReference;
				break;
			}
		}

		if (IsValid(FoundInventoryListItem)) {
			// Create a temporary item variable of one of the items to be swapped
			FItemBase TemporaryEquippedItemCopy = EquippedItem;
			FItemBase TemporaryItemSlotCopy;

			// Overwrite the first item with the second item
			//FoundInventoryListItem->ItemReference = SelectedItem;

			// Overwrite the second item with the temporary item duplicate variable
			//ClickedWidgetInventoryListItem->ItemReference = TemporaryEquippedItemCopy;

			// Apply the new data to the relevant variable
			TArray<UUserWidget*> FoundInventoryWidgets;
			UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), FoundInventoryWidgets, UWidgetMenuInventory::StaticClass(), false);
			if (FoundInventoryWidgets.Num() > 0) {
				if (Cast<UWidgetMenuInventory>(FoundInventoryWidgets[0])) {
					UWidgetMenuInventory* InventoryWidget = Cast<UWidgetMenuInventory>(FoundInventoryWidgets[0]);

					// To-Do: Make this work for every type of weapon and armour slot
					if (SelectedItem.ItemType == EItemTypes::Weapon) {
						//InventoryWidget->OwningEntityInventoryComponent->EquippedPrimaryWeapon = SelectedItem;
					} else if (SelectedItem.ItemType == EItemTypes::Armour) {
						//InventoryWidget->OwningEntityInventoryComponent->EquippedChestItem = SelectedItem;
					} else if (SelectedItem.ItemType == EItemTypes::Consumable) {
						//InventoryWidget->OwningEntityInventoryComponent->EquippedQuickUseItem = SelectedItem;
					}

					// Refresh the inventory widget
					InventoryWidget->PopulateUnequippedItemsScrollBox(InventoryWidget->OwningEntityInventoryComponent);
					InventoryWidget->PopulateEquippedItemsScrollBox(InventoryWidget->OwningEntityInventoryComponent);
					InventoryWidget->RefreshOtherSlots(InventoryWidget->OwningEntityInventoryComponent);
				}
			}
		} else {
			UE_LOG(LogTemp, Warning, TEXT("UWidgetItemRightClickMenu / EquipButtonPressed() / Error: Could not find InventoryListItem widget to swap items."));
		}
		//}
	} else {
		UE_LOG(LogTemp, Warning, TEXT("UWidgetItemRightClickMenu / EquipButtonPressed() / Warning: Cannot equip items with the SlotType None."));
	}

	// 'Close' the right click menu
	this->SetVisibility(ESlateVisibility::Collapsed);
}


void UWidgetItemRightClickMenu::UnequipButtonPressed()
{

}