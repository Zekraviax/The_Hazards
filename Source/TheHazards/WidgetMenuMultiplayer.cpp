#include "WidgetMenuMultiplayer.h"


#include "EntityPlayerCharacter.h"
#include "WidgetMenuFindSessions.h"
#include "WidgetMenuHostSession.h"


void UWidgetMenuMultiplayer::OpenHostSessionMenu()
{
	// Use the player character to get widget classes and open widgets
	AEntityPlayerCharacter* const PlayerCharacter = Cast<AEntityPlayerCharacter>(GetGameInstance()->GetFirstLocalPlayerController()->GetPawn());

	if (PlayerCharacter->IsValidLowLevel()) {
		PlayerCharacter->OpenWidgetByClass(PlayerCharacter->WidgetMenuHostSessionClass);
	}
}


void UWidgetMenuMultiplayer::OpenFindSessionMenu()
{
	// Use the player character to get widget classes and open widgets
	AEntityPlayerCharacter* const PlayerCharacter = Cast<AEntityPlayerCharacter>(GetGameInstance()->GetFirstLocalPlayerController()->GetPawn());

	if (PlayerCharacter->IsValidLowLevel()) {
		PlayerCharacter->OpenWidgetByClass(PlayerCharacter->WidgetMenuFindSessionsClass);
	}
}