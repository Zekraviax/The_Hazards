#include "WidgetSessionListEntry.h"


#include "TheHazardsGameInstanceSubsystem.h"


void UWidgetSessionListEntry::JoinSession()
{
	// Convert session name from FText to FName
	FString SessionNameAsString = SessionNameText->GetText().ToString();

	// Create an instance of a LocalPlayer so we can get a unique ID from it
	ULocalPlayer* const LocalPlayer = GetGameInstance()->GetFirstGamePlayer();

	// Join the sessions
	GetGameInstance()->GetSubsystem<UTheHazardsGameInstanceSubsystem>()->JoinSession(LocalPlayer->GetPreferredUniqueNetId().GetUniqueNetId(), FName(*SessionNameAsString), Session);
}