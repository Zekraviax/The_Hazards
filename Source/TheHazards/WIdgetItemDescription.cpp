#include "WidgetItemDescription.h"


void UWidgetItemDescription::SetDescriptionText(FItemBase ItemReference)
{
	FString DescriptionString = "Name: " + ItemReference.Name + "\nItem Type: " + UEnum::GetDisplayValueAsText(ItemReference.ItemType).ToString();

	if (ItemReference.ItemType == EItemTypes::Weapon) {
		DescriptionString.Append("\nDamage Per Shot: " + FString::SanitizeFloat(ItemReference.WeaponData.DamagePerShot));
	} else if (ItemReference.ItemType == EItemTypes::Part) {
		DescriptionString.Append("\nPart Type: " + UEnum::GetDisplayValueAsText(ItemReference.PartData.PartType).ToString());
	}

	Description->SetText(FText::FromString(DescriptionString));
}