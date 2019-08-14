// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseClass_Widget_Inventory.h"

#include "Entity_Base.h"
#include "SubWidget_ItemDrag.h"
#include "SubWidget_SkillTreeSlot.h"


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
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("Mouse Up: Inventory"));

	WidgetTree->ForEachWidget([&](UWidget* Widget) {
		check(Widget);
		if (Widget->IsA(USubWidget_ItemDrag::StaticClass())) {
			USubWidget_ItemDrag* ItemDragWidget = Cast<USubWidget_ItemDrag>(Widget);

			if (ItemDragWidget)
			{
				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("Found ItemDrag Widget"));
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

void UBaseClass_Widget_Inventory::RunTest()
{

}