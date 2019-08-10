// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseClass_Widget_ItemDescription.h"

void UBaseClass_Widget_ItemDescription::SetText()
{
	// Text Variables for Enums
	FString ItemSupertype_String;
	FString EquipSlot_String;

	switch (ItemReference.Supertype)
	{
	case(E_Item_Supertypes::E_Weapon):
		ItemSupertype_String = "Weapon";
		break;
	default:
		ItemSupertype_String = "Error";
		break;
	}

	if (ItemReference.Amount > 0) {
		Name->SetText(FText::FromString(ItemReference.Name));

		switch (ItemReference.Supertype)
		{
		// Set Weapon Description
		case(E_Item_Supertypes::E_Weapon):
			switch (ItemReference.Weapon.EquipSlot)
			{
			case(E_Weapon_EquipSlot::E_Primary):
				EquipSlot_String = "Primary";
				break;
			case(E_Weapon_EquipSlot::E_Secondary):
				EquipSlot_String = "Secondary";
				break;
			case(E_Weapon_EquipSlot::E_Tertiary):
				EquipSlot_String = "Tertiary";
				break;
			default:
				EquipSlot_String = "Error";
				break;
			}

			Description->SetText(FText::FromString("Item Type: " + ItemSupertype_String 
				+ "\nEquip Slot: " + EquipSlot_String 
				+ "\nDamage Per Shot: " + FString::SanitizeFloat(ItemReference.Weapon.DamagePerShot)
				+ "\nAttack Speed Multiplier: " + FString::SanitizeFloat(ItemReference.Weapon.AttackSpeedMultiplier) + "x"));
			break;
		default:
			Description->SetText(FText::FromString("Error"));
			break;
		}
	}
	//else {
	//	this->RemoveFromParent();
	//}
}