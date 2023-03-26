#include "WIdgetItemDescription.h"


void UWIdgetItemDescription::SetDescriptionText(FItemBase ItemReference)
{
	FString DescriptionString = "Name: " + ItemReference.Name;

	if (ItemReference.ItemType == EItemTypes::Weapon) {
		DescriptionString.Append("\nDamage Per Shot: " + FString::SanitizeFloat(ItemReference.WeaponData.DamagePerShot));
	}

	Description->SetText(FText::FromString(DescriptionString));
}