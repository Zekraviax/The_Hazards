#include "WidgetHudBattle.h"


void UWidgetHudBattle::UpdateAuraPointsText(float Current, float Maximum)
{
	AuraPointsText->SetText(FText::FromString("AP: " + FString::FromInt(FMath::TruncToInt(Current)) + " / " + FString::FromInt(FMath::TruncToInt(Maximum))));
}