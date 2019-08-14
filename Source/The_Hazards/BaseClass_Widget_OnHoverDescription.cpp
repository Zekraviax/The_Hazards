// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseClass_Widget_OnHoverDescription.h"

void UBaseClass_Widget_OnHoverDescription::SetText(E_Description_Supertypes Supertype)
{
	// Text variables for Item enums
	FString ItemSupertype_String;
	FString EquipSlot_String;

	// Text variables for Skill enums
	FString SkillElementType_String;

	switch (Supertype)
	{
		case(E_Description_Supertypes::E_Skill):
		{
			switch (SkillReference.Element)
			{
				case(E_Character_Elements::E_Aer):
					SkillElementType_String = "Aer";
					break;
				default:
					SkillElementType_String = "Error";
					break;
			}

			Name->SetText(FText::FromString(SkillReference.Name));
			Description->SetText(FText::FromString("Element: " + SkillElementType_String
				+ "\nLevel : " + FString::FromInt(SkillReference.CurrentLevel) + " / " + FString::FromInt(SkillReference.MaximumLevel)));
				//+ "\nDamage Per Shot: " + FString::SanitizeFloat(ItemReference.Weapon.DamagePerShot)
				//+ "\nAttack Speed Multiplier: " + FString::SanitizeFloat(ItemReference.Weapon.AttackSpeedMultiplier) + "x"));
		}

		case(E_Description_Supertypes::E_Item):
		{
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

					Name->SetText(FText::FromString(ItemReference.Name));
					Description->SetText(FText::FromString("Item Type: " + ItemSupertype_String
						+ "\nEquip Slot: " + EquipSlot_String
						+ "\nDamage Per Shot: " + FString::SanitizeFloat(ItemReference.Weapon.DamagePerShot)
						+ "\nAttack Speed Multiplier: " + FString::SanitizeFloat(ItemReference.Weapon.AttackSpeedMultiplier) + "x"));
					break;
				}
			}
		}
	}
	//else {
	//	this->RemoveFromParent();
	//}
}