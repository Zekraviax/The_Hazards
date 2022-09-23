#include "WidgetMenuMultiplayer.h"


#include "EntityBaseCharacter.h"
#include "TheHazardsPlayerController.h"
#include "WidgetMenuFindSessions.h"
#include "WidgetMenuHostSession.h"


void UWidgetMenuMultiplayer::OpenHostSessionMenu()
{
	// Use the player's controller to get widget classes and open widgets
	ATheHazardsPlayerController* const PlayerController = Cast<ATheHazardsPlayerController>(GetGameInstance()->GetFirstLocalPlayerController());

	if (PlayerController->IsValidLowLevel()) {
		PlayerController->OpenWidgetByClass(PlayerController->WidgetMenuHostSessionClass);
	}
}


void UWidgetMenuMultiplayer::OpenFindSessionMenu()
{
	// Use the player's controller to get widget classes and open widgets
	ATheHazardsPlayerController* const PlayerController = Cast<ATheHazardsPlayerController>(GetGameInstance()->GetFirstLocalPlayerController());

	if (PlayerController->IsValidLowLevel()) {
		PlayerController->OpenWidgetByClass(PlayerController->WidgetMenuFindSessionsClass);
	}
}