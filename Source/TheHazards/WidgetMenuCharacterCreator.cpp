#include "WidgetMenuCharacterCreator.h"


#include "SaveGamePlayerData.h"
#include "TheHazardsGameInstance.h"


void UWidgetMenuCharacterCreator::PopulateDropdowns()
{
	const UEnum* RacesEnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("ERaces"), true);
	const UEnum* ElementsEnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EElements"), true);

	if (RacesEnumPtr != nullptr) {
		for (int i = 0; i < RacesEnumPtr->NumEnums() - 1; i++) {
			RacesDropdown->AddOption(RacesEnumPtr->GetNameByIndex(i).ToString());
		}

		RacesDropdown->SetSelectedOption(RacesEnumPtr->GetNameByIndex(0).ToString());
	}

	if (ElementsEnumPtr != nullptr) {
		for (int i = 0; i < ElementsEnumPtr->NumEnums() - 1; i++) {
			ElementsDropdown->AddOption(ElementsEnumPtr->GetNameByIndex(i).ToString());
		}

		ElementsDropdown->SetSelectedOption(ElementsEnumPtr->GetNameByIndex(0).ToString());
	}

	//PlayerCharacterName->OnBeginEditByDesigner
}


void UWidgetMenuCharacterCreator::SavePlayerCharacter()
{
	//FEntityBaseData PlayerDataStruct = Cast<UTheHazardsGameInstance>(GetGameInstance())->GetPlayerSaveObject()->PlayerData;

	Cast<UTheHazardsGameInstance>(GetGameInstance())->GetPlayerSaveObject()->PlayerData.Name = PlayerCharacterName->GetText().ToString();

	int32 RacesIndex = StaticEnum<ERaces>()->GetIndexByNameString(RacesDropdown->GetSelectedOption());
	Cast<UTheHazardsGameInstance>(GetGameInstance())->GetPlayerSaveObject()->PlayerData.Race = static_cast<ERaces>((uint8)RacesIndex);

	int32 ElementIndex = StaticEnum<EElements>()->GetIndexByNameString(ElementsDropdown->GetSelectedOption());
	Cast<UTheHazardsGameInstance>(GetGameInstance())->GetPlayerSaveObject()->PlayerData.Element = static_cast<EElements>((uint8)RacesIndex);

	Cast<UTheHazardsGameInstance>(GetGameInstance())->GetPlayerSaveObject()->SavePlayerDataToJson();
}