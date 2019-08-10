// Fill out your copyright notice in the Description page of Project Settings.


#include "SubWidget_InventorySlot.h"

void USubWidget_InventorySlot::UpdateSlot()
{
	ItemAmountBind = ItemStruct.Amount;
	
	if (ItemStruct.InventoryImage) {
		ItemImage->SetBrushFromTexture(ItemStruct.InventoryImage, true);
	}
	else {
		ItemImage->SetBrushFromTexture(NULL, true);
	}
}

void USubWidget_InventorySlot::OnMouseDown()
{
	if (ItemDrag_Class && ItemStruct.Amount > 0) {
		ItemDrag_Reference = CreateWidget<USubWidget_ItemDrag>(GetWorld(), ItemDrag_Class);
		ItemDrag_Reference->SlotReference = this;
		ItemDrag_Reference->ItemStruct = ItemStruct;
		ItemDrag_Reference->SetImage();
		ItemDrag_Reference->AddToViewport();

		ItemImage->SetBrushFromTexture(NULL, true);
	}
}

void USubWidget_InventorySlot::OnMouseUp()
{
	for (TObjectIterator<USubWidget_InventorySlot> Itr; Itr; ++Itr)
	{
		USubWidget_InventorySlot *FoundInventorySlot = *Itr;

		if (FoundInventorySlot->ItemDrag_Reference) {

			USubWidget_ItemDrag *FoundSlot = FoundInventorySlot->ItemDrag_Reference;
			F_Item_BaseStruct TempItemVariable = FoundSlot->ItemStruct;

			//switch (FoundSlot->ItemStruct.Supertype)
			//{
			//case(E_Item_Supertypes::E_Weapon):
			//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("Weapon"));
			//	break;
			//case(E_Item_Supertypes::E_Armour):
			//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("Armour"));
			//	break;
			//case(E_Item_Supertypes::E_Ammo):
			//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("Ammo"));
			//	break;
			//case(E_Item_Supertypes::E_Collectable):
			//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("Collectable"));
			//	break;
			//case(E_Item_Supertypes::E_Consumable):
			//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("Consumable"));
			//	break;
			//case(E_Item_Supertypes::E_CustomPart):
			//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("Custom Part"));
			//	break;
			//case(E_Item_Supertypes::E_Miscellaneous):
			//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("Miscellaneous"));
			//	break;
			//default:
			//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("Error"));
			//	break;
			//}

			// Switch on slot type and item type in dragged slot
			// Drag weapon onto weapon slot
			if (SlotType == E_InventorySlot_SlotType::E_EquipmentSlot && FoundSlot->ItemStruct.Supertype == E_Item_Supertypes::E_Weapon) {
				//switch (FoundSlot->ItemStruct.Weapon.EquipSlot)
				//{
				//case(E_Weapon_EquipSlot::E_Tertiary):
				//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("Weapon Equip Slot: Tertiary"));
				//	break;
				//case(E_Weapon_EquipSlot::E_Primary):
				//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("Weapon Equip Slot: Primary"));
				//	break;
				//case(E_Weapon_EquipSlot::E_Secondary):
				//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("Weapon Equip Slot: Secondary"));
				//	break;
				//default:
				//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("Weapon Equip Slot: Error"));
				//	break;
				//}
				//switch (EquipmentSlotType)
				//{
				//case(E_InventorySlot_EquipType::E_Weapon_Tertiary):
				//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("Inventory Equip Slot: Tertiary"));
				//	break;
				//case(E_InventorySlot_EquipType::E_Weapon_Primary):
				//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("Inventory Equip Slot: Primary"));
				//	break;
				//case(E_InventorySlot_EquipType::E_Weapon_Secondary):
				//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("Inventory Equip Slot: Secondary"));
				//	break;
				//default:
				//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("Inventory Equip Slot: Error"));
				//	break;
				//}
				if (EquipmentSlotType == E_InventorySlot_EquipType::E_Weapon_Primary && FoundSlot->ItemStruct.Weapon.EquipSlot == E_Weapon_EquipSlot::E_Primary ||
					EquipmentSlotType == E_InventorySlot_EquipType::E_Weapon_Secondary && FoundSlot->ItemStruct.Weapon.EquipSlot == E_Weapon_EquipSlot::E_Secondary ||
					EquipmentSlotType == E_InventorySlot_EquipType::E_Weapon_Tertiary && FoundSlot->ItemStruct.Weapon.EquipSlot == E_Weapon_EquipSlot::E_Tertiary) {

					FoundSlot->SlotReference->ItemStruct = ItemStruct;
					ItemStruct = TempItemVariable;

					FoundSlot->SlotReference->UpdateSlot();
					UpdateSlot();
				}
			}
			else if (SlotType == E_InventorySlot_SlotType::E_StandardSlot) {
				FoundSlot->SlotReference->ItemStruct = ItemStruct;
				ItemStruct = TempItemVariable;

				FoundSlot->SlotReference->UpdateSlot();
				UpdateSlot();
			}

			FoundSlot->SlotReference->ItemDrag_Reference = NULL;
			FoundSlot->RemoveFromParent();
		}
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