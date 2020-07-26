#include "BaseClass_Widget_Inventory.h"

#include "Entity_Base.h"
#include "SubWidget_ItemDrag.h"
#include "SubWidget_SkillTreeSlot.h"


void UBaseClass_Widget_Inventory::OnInventoryOpened()
{
	if (PlayerReference) {
		MoneyText->SetText(FText::FromString("Money: " + FString::FromInt(PlayerReference->Money)));
		ScrapText->SetText(FText::FromString("Scrap: " + FString::FromInt(PlayerReference->Scrap)));
	}
}


void UBaseClass_Widget_Inventory::PopulateInventorySlots()
{
	if (PlayerReference && WidgetTree) {
		// Get all inventory slot widgets and add to array
		WidgetTree->ForEachWidget([&](UWidget* Widget) {
			if (Widget->IsA(USubWidget_InventorySlot::StaticClass())) {
				InventorySlotsArray.Add(Cast<USubWidget_InventorySlot>(Widget));
				Cast<USubWidget_InventorySlot>(Widget)->PlayerReference = PlayerReference;
			}
		});

		// Get all items in player inventory and assign to inventory slots
		for (F_Item_BaseStruct &Item : PlayerReference->Inventory) {
			for (int i = 0; i < InventorySlotsArray.Num(); i++) {
				if (Item.IndexInInventoryArray == InventorySlotsArray[i]->InventorySlotIndex) {
					InventorySlotsArray[i]->ItemStruct = Item;
					InventorySlotsArray[i]->UpdateSlot();
				}
			}
		}
	}
}


void UBaseClass_Widget_Inventory::OnMouseUp()
{
	WidgetTree->ForEachWidget([&](UWidget* Widget) {
		check(Widget);
		if (Widget->IsA(USubWidget_ItemDrag::StaticClass())) {
			USubWidget_ItemDrag* ItemDragWidget = Cast<USubWidget_ItemDrag>(Widget);

			if (ItemDragWidget) {
				ItemDragWidget->RemoveFromParent();
			}
		}
	});

	WidgetTree->ForEachWidget([&](UWidget* Widget) {
		check(Widget);
		if (Widget->IsA(USubWidget_InventorySlot::StaticClass())) {
			USubWidget_InventorySlot* FoundSlot = Cast<USubWidget_InventorySlot>(Widget);

			if (FoundSlot)
				FoundSlot->UpdateSlot();
			
		}
	});
}