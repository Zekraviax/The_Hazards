#include "WidgetMenuPause.h"


#include "EntityPlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "SaveGamePlayerData.h"
#include "TheHazardsGameInstance.h"
#include "WidgetMenuOptions.h"
#include "WidgetMenuMultiplayer.h"


void UWidgetMenuPause::OpenMultiplayerMenu()
{
	// Use the player character to get widget classes and open widgets
	AEntityPlayerCharacter* const PlayerCharacter = Cast<AEntityPlayerCharacter>(GetGameInstance()->GetFirstLocalPlayerController()->GetPawn());

	if (PlayerCharacter->IsValidLowLevel()) {
		PlayerCharacter->OpenWidgetByClass(PlayerCharacter->WidgetMenuMultiplayerClass);
	}
}


void UWidgetMenuPause::OpenOptionsMenu()
{
	AEntityPlayerCharacter* const PlayerCharacter = Cast<AEntityPlayerCharacter>(GetGameInstance()->GetFirstLocalPlayerController()->GetPawn());

	if (PlayerCharacter->IsValidLowLevel()) {
		PlayerCharacter->OpenWidgetByClass(PlayerCharacter->WidgetMenuOptionsClass);
	}
}


void UWidgetMenuPause::SaveGame()
{
	Cast<UTheHazardsGameInstance>(GetGameInstance())->GetPlayerSaveObject()->SavePlayerDataToJson();
}


void UWidgetMenuPause::LoadGame()
{
	AEntityPlayerCharacter* const PlayerCharacter = Cast<AEntityPlayerCharacter>(GetGameInstance()->GetFirstLocalPlayerController()->GetPawn());

	USaveGamePlayerData* PlayerSaveObject = Cast<USaveGamePlayerData>(UGameplayStatics::CreateSaveGameObject(USaveGamePlayerData::StaticClass()));
	PlayerSaveObject->LoadPlayerDataFromJson(PlayerCharacter, "");
}


void UWidgetMenuPause::QuitGame()
{
	FGenericPlatformMisc::RequestExit(false);
}