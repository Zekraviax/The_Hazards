#include "WidgetMenuFindSessions.h"


#include "TheHazardsGameInstanceSubsystem.h"
#include "TheHazardsPlayerController.h"
#include "WidgetSessionListEntry.h"


void UWidgetMenuFindSessions::PopulateFoundSessionsScrollBox(TArray<FOnlineSessionSearchResult> FoundSessionsArray)
{
	UWidgetSessionListEntry* WidgetSessionListEntryReference;

	// Get the session widget blueprint class from the player controller
	ATheHazardsPlayerController* const PlayerController = Cast<ATheHazardsPlayerController>(GetGameInstance()->GetFirstLocalPlayerController());

	if (PlayerController->WidgetSessionListEntryClass->IsValidLowLevel()) {
		for (FOnlineSessionSearchResult Session : FoundSessionsArray) {
			WidgetSessionListEntryReference = CreateWidget<UWidgetSessionListEntry>(GetWorld(), PlayerController->WidgetSessionListEntryClass);

			// Set widget info
			WidgetSessionListEntryReference->Session = Session;
			WidgetSessionListEntryReference->SessionNameText->SetText(FText::FromString("Game"));
			WidgetSessionListEntryReference->HostNameText->SetText(FText::FromString(Session.Session.OwningUserName));

			FoundSessionsScrollBox->AddChild(WidgetSessionListEntryReference);
		}
	}
}


void UWidgetMenuFindSessions::BeginSearchForSessions()
{
	// Create an instance of a LocalPlayer so we can get a unique ID from it
	ULocalPlayer* const LocalPlayer = GetGameInstance()->GetFirstGamePlayer();

	// Search for sessions
	GetGameInstance()->GetSubsystem<UTheHazardsGameInstanceSubsystem>()->FindSessions(LocalPlayer->GetPreferredUniqueNetId().GetUniqueNetId(), true, false);
}