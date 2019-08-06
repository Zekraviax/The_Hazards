// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseClass_Widget_Inventory.h"

#include "Entity_Base.h"


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
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("Found Item"));
			for (int i = 0; i < InventorySlotsArray.Num(); i++) {
				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("Found Slot"));
				if (Item.IndexInInventoryArray == InventorySlotsArray[i]->InventorySlotIndex) {
					//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("Found Matching Item And Slot"));
					InventorySlotsArray[i]->ItemStruct = Item;
					InventorySlotsArray[i]->UpdateSlot();
				}
			}
		}
	}
}