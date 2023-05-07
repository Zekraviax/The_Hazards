#include "WidgetCraftingWindowDescription.h"


void UWidgetCraftingWindowDescription::SetText(FCraftingBlueprintSlotData InCraftingWindowSlotData)
{
	FString DescriptionText = UEnum::GetDisplayValueAsText(InCraftingWindowSlotData.PartType).ToString();
	DescriptionText.Append(" slot");

	Description->SetText(FText::FromString(DescriptionText));
}