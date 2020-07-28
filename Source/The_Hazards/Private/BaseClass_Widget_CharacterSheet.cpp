#include "BaseClass_Widget_CharacterSheet.h"

#include "Entity_Base.h"
#include "Entity_Player.h"


void UBaseClass_Widget_CharacterSheet::OpenCharacterSheet()
{
	// Set base variables
	if (PlayerReference) {
		// Set Name
		Name_Text->SetText(FText::FromString(PlayerReference->CharacterSheet.Name));

		// Switch for Race dropdown
		switch (PlayerReference->CharacterSheet.Race)
		{
		case(E_Character_Races::E_Chiropterrian):
			Race_Text->SetText(FText::FromString(TEXT("Chiropterrian")));
			break;
		case(E_Character_Races::E_Labaredian):
			Race_Text->SetText(FText::FromString(TEXT("Labaredian")));
			break;
		case(E_Character_Races::E_Detoling):
			Race_Text->SetText(FText::FromString(TEXT("Detoling")));
			break;
		case(E_Character_Races::E_Frostine):
			Race_Text->SetText(FText::FromString(TEXT("Frostine")));
			break;
		case(E_Character_Races::E_Celestial):
			Race_Text->SetText(FText::FromString(TEXT("Celestial")));
			break;
		default:
			Race_Text->SetText(FText::FromString(TEXT("Chiropterrian")));
			break;
		}

		// Switch for Element dropdown
		switch (PlayerReference->CharacterSheet.Element)
		{
		case(E_Character_Elements::E_Aer):
			Element_Text->SetText(FText::FromString(TEXT("Aer")));
			break;
		case(E_Character_Elements::E_Aqua):
			Element_Text->SetText(FText::FromString(TEXT("Aqua")));
			break;
		case(E_Character_Elements::E_Ignis):
			Element_Text->SetText(FText::FromString(TEXT("Ignis")));
			break;
		case(E_Character_Elements::E_Terra):
			Element_Text->SetText(FText::FromString(TEXT("Terra")));
			break;
		case(E_Character_Elements::E_Vita):
			Element_Text->SetText(FText::FromString(TEXT("Vita")));
			break;
		default:
			Element_Text->SetText(FText::FromString(TEXT("Aer")));
			break;
		}

		// Switch for Faction dropdown
		switch (PlayerReference->CharacterSheet.Faction)
		{
		case(E_Character_Factions::E_XRX):
			Faction_Text->SetText(FText::FromString(TEXT("XRX")));
			break;
		case(E_Character_Factions::E_TimesEnd):
			Faction_Text->SetText(FText::FromString(TEXT("Time's End")));
			break;
		case(E_Character_Factions::E_GaianGuardians):
			Faction_Text->SetText(FText::FromString(TEXT("Gaian Guardians")));
			break;
		case(E_Character_Factions::E_AscendantsReach):
			Faction_Text->SetText(FText::FromString(TEXT("Ascendant's Reach")));
			break;
		case(E_Character_Factions::E_GoldenGrasp):
			Faction_Text->SetText(FText::FromString(TEXT("Golden Grasp")));
			break;
		case(E_Character_Factions::E_NA):
			Faction_Text->SetText(FText::FromString(TEXT("N/A")));
			break;
		default:
			Faction_Text->SetText(FText::FromString(TEXT("N/A")));
			break;
		}

		// Set stats
		// Current Stats
		CurrentStatsColumn->SetText(FText::FromString("Current Stats: \n\n" + FString::FromInt(PlayerReference->CurrentStats.HealthPoints)
			+ "\n" + FString::SanitizeFloat(PlayerReference->CurrentStats.HealthPoints_RegenPerSecond)
			+ "\n" + FString::SanitizeFloat(PlayerReference->CurrentStats.HealthPoints_RegenStartDelay)
			+ "\n" + FString::FromInt(PlayerReference->CurrentStats.AuraPoints)
			+ "\n" + FString::SanitizeFloat(PlayerReference->CurrentStats.AuraPoints_RegenPerSecond)
			+ "\n" + FString::SanitizeFloat(PlayerReference->CurrentStats.AuraPoints_RegenStartDelay)
			+ "\n" + FString::FromInt(PlayerReference->CurrentStats.Physical_Strength)
			+ "\n" + FString::FromInt(PlayerReference->CurrentStats.Physical_Defence)
			+ "\n" + FString::FromInt(PlayerReference->CurrentStats.Elemental_Strength)
			+ "\n" + FString::FromInt(PlayerReference->CurrentStats.Elemental_Defence)
			+ "\n" + FString::FromInt(PlayerReference->CurrentStats.Attack_Speed)
			+ "\n" + FString::FromInt(PlayerReference->CurrentStats.Move_Speed)
			+ "\n" + FString::FromInt(PlayerReference->CurrentStats.Evasiveness)
			+ "\n" + FString::FromInt(PlayerReference->CurrentStats.Status_Potency)
			+ "\n" + FString::FromInt(PlayerReference->CurrentStats.Luck)));

		// Total Stats
		TotalStatsColumn->SetText(FText::FromString("Total Stats: \n\n" + FString::FromInt(PlayerReference->TotalStats.HealthPoints)
			+ "\n" + FString::SanitizeFloat(PlayerReference->TotalStats.HealthPoints_RegenPerSecond)
			+ "\n" + FString::SanitizeFloat(PlayerReference->TotalStats.HealthPoints_RegenStartDelay)
			+ "\n" + FString::FromInt(PlayerReference->TotalStats.AuraPoints)
			+ "\n" + FString::SanitizeFloat(PlayerReference->TotalStats.AuraPoints_RegenPerSecond)
			+ "\n" + FString::SanitizeFloat(PlayerReference->TotalStats.AuraPoints_RegenStartDelay)
			+ "\n" + FString::FromInt(PlayerReference->TotalStats.Physical_Strength)
			+ "\n" + FString::FromInt(PlayerReference->TotalStats.Physical_Defence)
			+ "\n" + FString::FromInt(PlayerReference->TotalStats.Elemental_Strength)
			+ "\n" + FString::FromInt(PlayerReference->TotalStats.Elemental_Defence)
			+ "\n" + FString::FromInt(PlayerReference->TotalStats.Attack_Speed)
			+ "\n" + FString::FromInt(PlayerReference->TotalStats.Move_Speed)
			+ "\n" + FString::FromInt(PlayerReference->TotalStats.Evasiveness)
			+ "\n" + FString::FromInt(PlayerReference->TotalStats.Status_Potency)
			+ "\n" + FString::FromInt(PlayerReference->TotalStats.Luck)));
	}
}

void UBaseClass_Widget_CharacterSheet::OpenStatBreakdown()
{
	if (StatBreakdown_Class && PlayerReference) {
		StatBreakdown_Reference = CreateWidget<USubWidget_StatBreakdown>(GetWorld(), StatBreakdown_Class);
		StatBreakdown_Reference->PlayerReference = PlayerReference;
		StatBreakdown_Reference->SetText();
		StatBreakdown_Reference->AddToViewport();

		Cast<AEntity_Player>(PlayerReference)->CurrentOpenMenuWidget = StatBreakdown_Reference;
		Cast<AEntity_Player>(PlayerReference)->CurrentOpenMenuWidget_Class = StatBreakdown_Class;

		RemoveFromParent();
	}
}