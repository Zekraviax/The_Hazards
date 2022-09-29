#include "WidgetMenuDeveloper.h"


#include "ActorComponentBaseStats.h"
#include "EntityPlayerCharacter.h"


void UWidgetMenuDeveloper::PopulateEditableTextBoxes()
{
	// To-Do: Replace this variable declaration with one in the .h file
	// so we aren't constantly running multiple functions to get the player's character
	if (!PlayerCharacter) {
		PlayerCharacter = Cast<AEntityPlayerCharacter>(GetGameInstance()->GetFirstLocalPlayerController()->GetPawn());
	}

	// Health and aura widgets
	EditCurrentHealthTextBox->SetText(FText::FromString(FString::SanitizeFloat(PlayerCharacter->GetBaseStatsComponent()->CurrentHealthPoints)));
	EditMaximumHealthTextBox->SetText(FText::FromString(FString::SanitizeFloat(PlayerCharacter->GetBaseStatsComponent()->MaximumHealthPoints)));
	EditCurrentAuraTextBox->SetText(FText::FromString(FString::SanitizeFloat(PlayerCharacter->GetBaseStatsComponent()->CurrentAuraPoints)));
	EditMaximumAuraTextBox->SetText(FText::FromString(FString::SanitizeFloat(PlayerCharacter->GetBaseStatsComponent()->MaximumAuraPoints)));
}


void UWidgetMenuDeveloper::EditCurrentHealth()
{
	if (!PlayerCharacter) {
		PlayerCharacter = Cast<AEntityPlayerCharacter>(GetGameInstance()->GetFirstLocalPlayerController()->GetPawn());
	}

	// Store the new current health in a temporary variable for testing purposes
	// Also prevents the 'update current health points' line from becoming too long
	float NewCurrentHealthValue = FCString::Atof(*EditCurrentHealthTextBox->GetText().ToString());

	PlayerCharacter->GetBaseStatsComponent()->CurrentHealthPoints = NewCurrentHealthValue;

	// Calling this function with a value of 0 still updates the HUD
	PlayerCharacter->GetBaseStatsComponent()->UpdateCurrentHealthPoints(0.f);
}


void UWidgetMenuDeveloper::EditMaximumHealth()
{
	if (!PlayerCharacter) {
		PlayerCharacter = Cast<AEntityPlayerCharacter>(GetGameInstance()->GetFirstLocalPlayerController()->GetPawn());
	}

	float NewMaximumHealthValue = FCString::Atof(*EditMaximumHealthTextBox->GetText().ToString());

	PlayerCharacter->GetBaseStatsComponent()->MaximumHealthPoints = NewMaximumHealthValue;
	PlayerCharacter->GetBaseStatsComponent()->UpdateCurrentHealthPoints(0.f);
}


void UWidgetMenuDeveloper::EditCurrentAura()
{
	if (!PlayerCharacter) {
		PlayerCharacter = Cast<AEntityPlayerCharacter>(GetGameInstance()->GetFirstLocalPlayerController()->GetPawn());
	}

	float NewCurrentAuraValue = FCString::Atof(*EditCurrentAuraTextBox->GetText().ToString());

	PlayerCharacter->GetBaseStatsComponent()->CurrentAuraPoints = NewCurrentAuraValue;
	PlayerCharacter->GetBaseStatsComponent()->UpdateCurrentAuraPoints(0.f);
}


void UWidgetMenuDeveloper::EditMaximumAura()
{
	if (!PlayerCharacter) {
		PlayerCharacter = Cast<AEntityPlayerCharacter>(GetGameInstance()->GetFirstLocalPlayerController()->GetPawn());
	}

	float NewMaximumAuraValue = FCString::Atof(*EditMaximumAuraTextBox->GetText().ToString());

	PlayerCharacter->GetBaseStatsComponent()->MaximumAuraPoints = NewMaximumAuraValue;
	PlayerCharacter->GetBaseStatsComponent()->UpdateCurrentAuraPoints(0.f);
}