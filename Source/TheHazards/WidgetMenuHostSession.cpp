#include "WidgetMenuHostSession.h"


#include "TheHazardsGameInstanceSubsystem.h"


void UWidgetMenuHostSession::LaunchSession()
{
	// Create an instance of a LocalPlayer so we can get a unique ID from it
	ULocalPlayer* const LocalPlayer = GetGameInstance()->GetFirstGamePlayer();

	// Attempt to host a session
	GetGameInstance()->GetSubsystem<UTheHazardsGameInstanceSubsystem>()->HostSession(LocalPlayer->GetPreferredUniqueNetId().GetUniqueNetId(), "SessionName", true, false, 2);
}