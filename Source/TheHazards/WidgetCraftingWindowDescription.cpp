#include "WidgetCraftingWindowDescription.h"


void UWidgetCraftingWindowDescription::SetText(FCraftingBlueprintSlotData InCraftingWindowSlotData, FItemBase InItemData)
{
	FString DescriptionText = UEnum::GetDisplayValueAsText(InCraftingWindowSlotData.PartType).ToString();
	DescriptionText.Append(" slot");

	DescriptionText.Append("\nName: " + InItemData.Name);

	Description->SetText(FText::FromString(DescriptionText));
}