#include "WidgetMenuPause.h"


#include "EntityPlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "SaveGamePlayerData.h"
#include "WidgetMenuMultiplayer.h"


void UWidgetMenuPause::OpenMultiplayerMenu()
{
	// Use the player character to get widget classes and open widgets
	AEntityPlayerCharacter* const PlayerCharacter = Cast<AEntityPlayerCharacter>(GetGameInstance()->GetFirstLocalPlayerController()->GetPawn());

	if (PlayerCharacter->IsValidLowLevel()) {
		PlayerCharacter->OpenWidgetByClass(PlayerCharacter->WidgetMenuMultiplayerClass);
	}
}


void UWidgetMenuPause::SaveGame()
{
	AEntityPlayerCharacter* const PlayerCharacter = Cast<AEntityPlayerCharacter>(GetGameInstance()->GetFirstLocalPlayerController()->GetPawn());

	USaveGamePlayerData* PlayerSaveObject = Cast<USaveGamePlayerData>(UGameplayStatics::CreateSaveGameObject(USaveGamePlayerData::StaticClass()));
	PlayerSaveObject->SavePlayerDataToJson(PlayerCharacter);
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