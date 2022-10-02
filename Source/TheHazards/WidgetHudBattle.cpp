#include "WidgetHudBattle.h"


void UWidgetHudBattle::UpdateHealthPointsInHud(float Current, float Maximum)
{
	if (HealthPointsText) {
		HealthPointsText->SetText(FText::FromString("HP: " + FString::FromInt(FMath::TruncToInt(Current)) + " / " + FString::FromInt(FMath::TruncToInt(Maximum))));
	}

	if (HealthPointsProgressBar) {
		HealthPointsProgressBar->SetPercent(Current / Maximum);
	}
}


void UWidgetHudBattle::UpdateAuraPointsInHud(float Current, float Maximum)
{
	if (AuraPointsText) {
		AuraPointsText->SetText(FText::FromString("AP: " + FString::FromInt(FMath::TruncToInt(Current)) + " / " + FString::FromInt(FMath::TruncToInt(Maximum))));
	}

	if (AuraPointsProgressBar) {
		AuraPointsProgressBar->SetPercent(Current / Maximum);
	}
}


void UWidgetHudBattle::UpdateLevelInHud(int Level)
{
	if (LevelText) {
		LevelText->SetText(FText::FromString("Level: " + FString::FromInt(Level)));
	}
}


void UWidgetHudBattle::UpdateExperiencePointsInHud(float Points)
{
	if (CurrentExperiencePointsText) {
		CurrentExperiencePointsText->SetText(FText::FromString("EXP: " + FString::FromInt(FMath::TruncToInt(Points))));
	}
}