#include "SubWidget_InventorySlot.h"

#include "BaseClass_Widget_Inventory.h"
#include "Entity_Base.h"


void USubWidget_InventorySlot::NativeTick(const FGeometry& MyGeometry, float DeltaTime)
{
	Super::NativeTick(MyGeometry, DeltaTime);

	//Item_TextBind();
}

void USubWidget_InventorySlot::UpdateSlot()
{
	ItemAmountBind = ItemStruct.Amount;
	
	Item_TextBind();

	if (ItemStruct.InventoryImage) {
		ItemImage->SetBrushFromTexture(ItemStruct.InventoryImage, true);
	} else {
		ItemImage->SetBrushFromTexture(NULL, true);
	}

	if (ItemDrag_Reference) {
		ItemDrag_Reference->RemoveFromParent();
		ItemDrag_Reference = NULL;
	}
}

void USubWidget_InventorySlot::OnMouseDown()
{
	if (ItemDrag_Class) {
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

			// Weapon
			// Switch on slot type and item type in dragged slot
			// Drag weapon onto weapon slot
			if (SlotType == E_InventorySlot_SlotType::E_EquipmentSlot && FoundSlot->ItemStruct.Supertype == E_Item_Supertypes::E_Weapon) {
				if (EquipmentSlotType == E_InventorySlot_EquipType::E_Weapon_Primary && FoundSlot->ItemStruct.Weapon.EquipSlot == E_Weapon_EquipSlot::E_Primary ||
					EquipmentSlotType == E_InventorySlot_EquipType::E_Weapon_Secondary && FoundSlot->ItemStruct.Weapon.EquipSlot == E_Weapon_EquipSlot::E_Secondary ||
					EquipmentSlotType == E_InventorySlot_EquipType::E_Weapon_Tertiary && FoundSlot->ItemStruct.Weapon.EquipSlot == E_Weapon_EquipSlot::E_Tertiary) {

					FoundSlot->SlotReference->ItemStruct = ItemStruct;
					ItemStruct = TempItemVariable;

					FoundSlot->SlotReference->UpdateSlot();
					UpdateSlot();

					if (PlayerReference) {
						for (F_Item_BaseStruct& Item : PlayerReference->Inventory) {
							if (Item.IndexInInventoryArray == FoundSlot->ItemStruct.IndexInInventoryArray) {
								Item.IndexInInventoryArray = InventorySlotIndex;
								break;
							}
						}

						// Set primary, secondary, and tertiary slots
						switch (ItemStruct.Weapon.EquipSlot)
						{
							case(E_Weapon_EquipSlot::E_Primary):
								PlayerReference->PrimaryWeapon = TempItemVariable;
								break;
							case(E_Weapon_EquipSlot::E_Secondary):
								PlayerReference->SecondaryWeapon = TempItemVariable;
								break;
							case(E_Weapon_EquipSlot::E_Tertiary):
								PlayerReference->TertiaryWeapon = TempItemVariable;
								break;
							default:
								break;
						}

						// Set equipped weapon
						if (PlayerReference->CurrentEquippedWeapon.Weapon.EquipSlot == FoundSlot->SlotReference->ItemStruct.Weapon.EquipSlot) {
							
							PlayerReference->CurrentEquippedWeapon = TempItemVariable;
							GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Equip weapon: " + PlayerReference->CurrentEquippedWeapon.Name));
						}

						PlayerReference->CalculateTotalStats();
					}
				}
			}

			// Armour
			// Drag equipment onto armour slot
			if (SlotType == E_InventorySlot_SlotType::E_EquipmentSlot && FoundSlot->ItemStruct.Supertype == E_Item_Supertypes::E_Armour) {
				if (EquipmentSlotType == E_InventorySlot_EquipType::E_Armour_Head && FoundSlot->ItemStruct.Armour.EquipSlot == E_Armour_EquipSlot::E_Head || 
					EquipmentSlotType == E_InventorySlot_EquipType::E_Armour_Body && FoundSlot->ItemStruct.Armour.EquipSlot == E_Armour_EquipSlot::E_Body || 
					EquipmentSlotType == E_InventorySlot_EquipType::E_Armour_Legs && FoundSlot->ItemStruct.Armour.EquipSlot == E_Armour_EquipSlot::E_Legs) 
				{
					FoundSlot->SlotReference->ItemStruct = ItemStruct;
					ItemStruct = TempItemVariable;

					FoundSlot->SlotReference->UpdateSlot();
					UpdateSlot();

					if (PlayerReference) {
						for (F_Item_BaseStruct& Item : PlayerReference->Inventory) {
							if (Item.IndexInInventoryArray == FoundSlot->ItemStruct.IndexInInventoryArray) {
								Item.IndexInInventoryArray = InventorySlotIndex;
								break;
							}
						}

						PlayerReference->CalculateTotalStats();
					}
				}
			}

			// Other Items
			// Swap any item to a standard slot
			else if (SlotType == E_InventorySlot_SlotType::E_StandardSlot) {
				FoundSlot->SlotReference->ItemStruct = ItemStruct;
				ItemStruct = TempItemVariable;

				FoundSlot->SlotReference->UpdateSlot();
				UpdateSlot();

				if (PlayerReference) {
					for (F_Item_BaseStruct& Item : PlayerReference->Inventory) {
						if (Item.IndexInInventoryArray == FoundSlot->ItemStruct.IndexInInventoryArray) {
							Item.IndexInInventoryArray = InventorySlotIndex;
							break;
						}
					}

					PlayerReference->CalculateTotalStats();
				}
			}

			FoundSlot->SlotReference->ItemDrag_Reference = NULL;
			FoundSlot->RemoveFromParent();
		}
	}

	for (TObjectIterator<UBaseClass_Widget_Inventory> Itr; Itr; ++Itr)
	{
		UBaseClass_Widget_Inventory* FoundSlot = *Itr;
		FoundSlot->OnMouseUp();
	}

}

void USubWidget_InventorySlot::OnMouseHoverBegin(FVector2D ScreenCoordinates)
{
	float PosX, PosY, ViewportScaledValueX, ViewportScaledValueY = 0;
	//float PosY = 0;
	int32 ViewportSizeX, ViewportSizeY;

	ItemDescription_Reference = CreateWidget<UBaseClass_Widget_OnHoverDescription>(GetWorld(), ItemDescription_Class);

	UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetViewportSize(ViewportSizeX, ViewportSizeY);
	ViewportScaledValueX = (1920 / ViewportSizeX);
	ViewportScaledValueY = (1080 / ViewportSizeY);

	if (SlotType == E_InventorySlot_SlotType::E_EquipmentSlot) {
		PosX = (ScreenCoordinates.X * ViewportScaledValueX) + 25;
		PosY = (ScreenCoordinates.Y * ViewportScaledValueY) - 100;
	}
	else if (SlotType == E_InventorySlot_SlotType::E_StandardSlot) {
		PosX = (ScreenCoordinates.X * ViewportScaledValueX) - 525;
		PosY = (ScreenCoordinates.Y * ViewportScaledValueY) - 100;
	}

	//if (PosY > 405)
	//	PosY = 405;

	//if (ItemStruct.Amount > 0 && ItemDescription_Class) {
		ItemDescription_Reference->SetPositionInViewport(FVector2D(PosX + 0.f, PosY + 0.f), false);
		ItemDescription_Reference->ItemReference = ItemStruct;
		ItemDescription_Reference->SetText(E_Description_Supertypes::E_Item);
		ItemDescription_Reference->AddToViewport();
	//}
	//else {
	//	if (ItemDescription_Reference) {
	//		ItemDescription_Reference->RemoveFromParent();
	//		ItemDescription_Reference = NULL;
	//	}
	//}
}

void USubWidget_InventorySlot::OnMouseHoverEnd()
{
	if (ItemDescription_Reference) {
		ItemDescription_Reference->RemoveFromParent();
		ItemDescription_Reference = NULL;
	}
}

void USubWidget_InventorySlot::Item_TextBind()
{
	if (SlotType == E_InventorySlot_SlotType::E_EquipmentSlot) {
		AmountText->SetText(FText::FromString(SlotDisplayName));
	}
	else if (SlotType == E_InventorySlot_SlotType::E_StandardSlot) {
		AmountText->SetText(FText::FromString(FString::FromInt(ItemStruct.Amount)));
	}

	//AmountText->SetText(FText::FromString(FString::FromInt(InventorySlotIndex)));
}