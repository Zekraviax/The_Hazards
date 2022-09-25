#include "WidgetMenuPause.h"


#include "EntityPlayerCharacter.h"
#include "WidgetMenuMultiplayer.h"


void UWidgetMenuPause::OpenMultiplayerMenu()
{
	// Use the player character to get widget classes and open widgets
	AEntityPlayerCharacter* const PlayerCharacter = Cast<AEntityPlayerCharacter>(GetGameInstance()->GetFirstLocalPlayerController()->GetPawn());

	if (PlayerCharacter->IsValidLowLevel()) {
		PlayerCharacter->OpenWidgetByClass(PlayerCharacter->WidgetMenuMultiplayerClass);
	}
}