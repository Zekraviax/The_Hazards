// Fill out your copyright notice in the Description page of Project Settings.


#include "SubWidget_InventorySlot.h"

void USubWidget_InventorySlot::UpdateSlot()
{
	ItemAmountBind = ItemStruct.Amount;
}

void USubWidget_InventorySlot::OnMouseDown()
{
	if (ItemDrag_Class) {
		ItemDrag_Reference = CreateWidget<USubWidget_ItemDrag>(GetWorld(), ItemDrag_Class);
		ItemDrag_Reference->AddToViewport();
	}
}