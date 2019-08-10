// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseClass_Widget_Inventory.h"

#include "Entity_Base.h"
#include "SubWidget_ItemDrag.h"


void UBaseClass_Widget_Inventory::PopulateInventorySlots()
{
	if (PlayerReference && WidgetTree) {
		// Get all inventory slot widgets and add to array
		WidgetTree->ForEachWidget([&](UWidget* Widget) {
			if (Widget->IsA(USubWidget_InventorySlot::StaticClass()) && Cast<USubWidget_InventorySlot>(Widget)->SlotType == E_InventorySlot_SlotType::E_StandardSlot) {
				InventorySlotsArray.Add(Cast<USubWidget_InventorySlot>(Widget));
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
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("Mouse Up: Inventory"));

	for (TObjectIterator<USubWidget_ItemDrag> Itr; Itr; ++Itr)
	{
		USubWidget_ItemDrag *FoundWidget = *Itr;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("Found ItemDrag Widget"));
		FoundWidget->RemoveFromParent();
	}

	// Reset inventory slot images
	for (TObjectIterator<USubWidget_InventorySlot> Itr; Itr; ++Itr)
	{
		USubWidget_InventorySlot *FoundInventorySlot = *Itr;
		FoundInventorySlot->UpdateSlot();
	}
}