// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseClass_Widget_CharCreator.h"

#include "Entity_Base.h"
#include "Entity_Player.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

void UBaseClass_Widget_CharCreator::FinalizeCharacter()
{
	if (PlayerReference) {
		// Set Name
		PlayerReference->CharacterSheet.Name = Name_TextBox->GetText().ToString();

		// Switch for Race dropdown
		switch (Race_DropDown->GetSelectedIndex())
		{
		case(0):
			PlayerReference->CharacterSheet.Race = E_Character_Races::E_Chiropterrian;
			break;
		case(1):
			PlayerReference->CharacterSheet.Race = E_Character_Races::E_Labaredian;
			break;
		case(2):
			PlayerReference->CharacterSheet.Race = E_Character_Races::E_Detoling;
			break;
		case(3):
			PlayerReference->CharacterSheet.Race = E_Character_Races::E_Frostine;
			break;
		case(4):
			PlayerReference->CharacterSheet.Race = E_Character_Races::E_Celestial;
			break;
		default:
			PlayerReference->CharacterSheet.Race = E_Character_Races::E_Chiropterrian;
			break;
		}

		// Switch for Element dropdown
		switch (Element_DropDown->GetSelectedIndex())
		{
		case(0):
			PlayerReference->CharacterSheet.Element = E_Character_Elements::E_Aer;
			break;
		case(1):
			PlayerReference->CharacterSheet.Element = E_Character_Elements::E_Aqua;
			break;
		case(2):
			PlayerReference->CharacterSheet.Element = E_Character_Elements::E_Ignis;
			break;
		case(3):
			PlayerReference->CharacterSheet.Element = E_Character_Elements::E_Terra;
			break;
		case(4):
			PlayerReference->CharacterSheet.Element = E_Character_Elements::E_Vita;
			break;
		default:
			PlayerReference->CharacterSheet.Element = E_Character_Elements::E_Aer;
			break;
		}

		// Switch for Faction dropdown
		switch (Faction_DropDown->GetSelectedIndex())
		{
		case(0):
			PlayerReference->CharacterSheet.Faction = E_Character_Factions::E_XRX;
			break;
		case(1):
			PlayerReference->CharacterSheet.Faction = E_Character_Factions::E_TimesEnd;
			break;
		case(2):
			PlayerReference->CharacterSheet.Faction = E_Character_Factions::E_GaianGuardians;
			break;
		case(3):
			PlayerReference->CharacterSheet.Faction = E_Character_Factions::E_AscendantsReach;
				break;
		case(4):
			PlayerReference->CharacterSheet.Faction = E_Character_Factions::E_GoldenGrasp;
				break;
		case(5):
			PlayerReference->CharacterSheet.Faction = E_Character_Factions::E_NA;
				break;
		default:
			PlayerReference->CharacterSheet.Faction = E_Character_Factions::E_NA;
			break;
		}

		// After everything has been finalized, close widget and resume gameplay
		Cast<AEntity_Player>(PlayerReference)->CurrentOpenMenuWidget = NULL;
		Cast<AEntity_Player>(PlayerReference)->CurrentOpenMenuWidget_Class = NULL;
		UGameplayStatics::SetGamePaused(GetWorld(), false);
		RemoveFromParent();
	}
}