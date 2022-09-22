#include "WidgetMenuPause.h"


#include "TheHazardsPlayerController.h"
#include "WidgetMenuMultiplayer.h"


void UWidgetMenuPause::OpenMultiplayerMenu()
{
	// Tell the player controller to swap widgets in the viewport
	ATheHazardsPlayerController* const PlayerController = Cast<ATheHazardsPlayerController>(GetGameInstance()->GetFirstLocalPlayerController());

	if (PlayerController->IsValidLowLevel()) {
		PlayerController->OpenWidgetByClass(PlayerController->WidgetMenuMultiplayerClass);
	}
}