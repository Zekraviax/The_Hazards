#include "WidgetHudBattle.h"


void UWidgetHudBattle::UpdateHealthPointsInHud(float Current, float Maximum)
{
	HealthPointsText->SetText(FText::FromString("HP: " + FString::FromInt(FMath::TruncToInt(Current)) + " / " + FString::FromInt(FMath::TruncToInt(Maximum))));

	HealthPointsProgressBar->SetPercent(Current / Maximum);
}


void UWidgetHudBattle::UpdateAuraPointsInHud(float Current, float Maximum)
{
	AuraPointsText->SetText(FText::FromString("AP: " + FString::FromInt(FMath::TruncToInt(Current)) + " / " + FString::FromInt(FMath::TruncToInt(Maximum))));

	AuraPointsProgressBar->SetPercent(Current / Maximum);
}