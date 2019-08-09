// Fill out your copyright notice in the Description page of Project Settings.


#include "SubWidget_InventorySlot.h"

void USubWidget_InventorySlot::UpdateSlot()
{
	ItemAmountBind = ItemStruct.Amount;
}

void USubWidget_InventorySlot::OnMouseDown()
{
	if (ItemDrag_Class && ItemStruct.Amount > 0) {
		ItemDrag_Reference = CreateWidget<USubWidget_ItemDrag>(GetWorld(), ItemDrag_Class);
		ItemDrag_Reference->SlotReference = this;
		ItemDrag_Reference->AddToViewport();
	}
}

void USubWidget_InventorySlot::OnMouseUp()
{
	for (TObjectIterator<USubWidget_ItemDrag> Itr; Itr; ++Itr)
	{
		USubWidget_ItemDrag *FoundWidget = *Itr;
		FoundWidget->RemoveFromParent();
	}
}

void USubWidget_InventorySlot::OnMouseHoverBegin(FVector2D Coordinates)
{
	float PosX;
	float PosY;
	int32 ViewportSizeX;
	int32 ViewportSizeY;
	float ViewportScaledValueX;
	float ViewportScaledValueY;

	ItemDescription_Reference = CreateWidget<UBaseClass_Widget_ItemDescription>(GetWorld(), ItemDescription_Class);

	UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetViewportSize(ViewportSizeX, ViewportSizeY);

	ViewportScaledValueX = (1920 / ViewportSizeX);
	ViewportScaledValueY = (1080 / ViewportSizeY);

	if (SlotType == E_InventorySlot_SlotType::E_EquipmentSlot) {
		PosX = (Coordinates.X * ViewportScaledValueX) + 5;
		PosY = (Coordinates.Y * ViewportScaledValueY) + 5;
	}
	else if (SlotType == E_InventorySlot_SlotType::E_StandardSlot) {
		PosX = (Coordinates.X * ViewportScaledValueX) - 555;
		PosY = (Coordinates.Y * ViewportScaledValueY) + 5;
	}

	if (PosY > 405)
		PosY = 405;

	if (ItemStruct.Amount > 0 && ItemDescription_Class) {
		ItemDescription_Reference->SetPositionInViewport(FVector2D(PosX + 0.f, PosY + 0.f), false);
		ItemDescription_Reference->ItemReference = ItemStruct;
		ItemDescription_Reference->SetText();
		ItemDescription_Reference->AddToViewport();
	}
	else {
		ItemDescription_Reference->RemoveFromParent();
		ItemDescription_Reference = NULL;
	}
}

void USubWidget_InventorySlot::OnMouseHoverEnd()
{
	if (ItemDescription_Reference) {
		ItemDescription_Reference->RemoveFromParent();
		ItemDescription_Reference = NULL;
	}

	//for (TObjectIterator<UBaseClass_Widget_ItemDescription> Itr; Itr; ++Itr)
	//{
	//	UBaseClass_Widget_ItemDescription *FoundWidget = *Itr;
	//	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("Found ItemDescription Widget"));
	//	FoundWidget->RemoveFromParent();
	//}
}