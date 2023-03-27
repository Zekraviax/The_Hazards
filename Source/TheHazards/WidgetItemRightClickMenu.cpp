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

		// Overwrite the first item with the second item
		FoundInventoryListItem->ItemReference = SelectedItem;

		// Overwrite the second item with the temporary item duplicate variable
		ClickedWidgetInventoryListItem->ItemReference = TemporaryEquippedItemCopy;

		// Apply the new data to the relevant variable
		TArray<UUserWidget*> FoundInventoryWidgets;
		UWidgetBlueprintLibrary::GetAllWidgetsOfClass(GetWorld(), FoundInventoryWidgets, UWidgetMenuInventory::StaticClass(), false);
		if (FoundInventoryWidgets.Num() > 0) {
			if (Cast<UWidgetMenuInventory>(FoundInventoryWidgets[0])) {
				UWidgetMenuInventory* InventoryWidget = Cast<UWidgetMenuInventory>(FoundInventoryWidgets[0]);

				if (SelectedItem.ItemType == EItemTypes::Weapon) {
					InventoryWidget->OwningEntityInventoryComponent->EquippedPrimaryWeapon = SelectedItem;
				}
			}
		}

		// 'Close' the right click menu
		this->SetVisibility(ESlateVisibility::Collapsed);
	} else {
		UE_LOG(LogTemp, Warning, TEXT("UWidgetItemRightClickMenu / EquipButtonPressed() / Error: Could not find InventoryListItem widget to swap items."));
	}
}


void UWidgetItemRightClickMenu::UnequipButtonPressed()
{

}