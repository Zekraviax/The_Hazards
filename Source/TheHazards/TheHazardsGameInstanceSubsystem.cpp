#include "TheHazardsGameInstanceSubsystem.h"


#include "Kismet/GameplayStatics.h"
#include "OnlineSessionSettings.h"
#include "OnlineSubsystem.h"


UTheHazardsGameInstanceSubsystem::UTheHazardsGameInstanceSubsystem(const FObjectInitializer& ObjectInitializer)
{
	// Bind delegates for handling creating and starting sessions
	OnCreateSessionCompleteDelegate = FOnCreateSessionCompleteDelegate::CreateUObject(this, &UTheHazardsGameInstanceSubsystem::OnCreateSessionComplete);
	OnStartSessionCompleteDelegate = FOnStartSessionCompleteDelegate::CreateUObject(this, &UTheHazardsGameInstanceSubsystem::OnStartSessionComplete);

	// Bind delegate for handling finding sessions
	OnFindSessionsCompleteDelegate = FOnFindSessionsCompleteDelegate::CreateUObject(this, &UTheHazardsGameInstanceSubsystem::OnFindSessionsComplete);

	// Bind delegate for handling joining sessions
	OnJoinSessionCompleteDelegate = FOnJoinSessionCompleteDelegate::CreateUObject(this, &UTheHazardsGameInstanceSubsystem::OnJoinSessionComplete);
}


bool UTheHazardsGameInstanceSubsystem::HostSession(TSharedPtr<const FUniqueNetId> UserId, FName SessionName, bool IsLanMatch, bool IsPresence, int32 MaxNumPlayers)
{
	// Get the OnlineSubsystem
	IOnlineSubsystem* const OnlineSubsystem = IOnlineSubsystem::Get();

	if (OnlineSubsystem) {
		// Get the online subsystem's session interface in order to create a session
		IOnlineSessionPtr SessionInterface = OnlineSubsystem->GetSessionInterface();

		if (SessionInterface.IsValid() && UserId.IsValid()) {
			// To-Do: Explain this
			SessionSettings = MakeShareable(new FOnlineSessionSettings());

			// Set the session options
			SessionSettings->bIsLANMatch = IsLanMatch;
			SessionSettings->bUsesPresence = IsPresence;
			SessionSettings->NumPublicConnections = MaxNumPlayers;
			SessionSettings->NumPrivateConnections = 0;
			SessionSettings->bAllowInvites = true;
			SessionSettings->bAllowJoinInProgress = true;
			SessionSettings->bShouldAdvertise = true;
			SessionSettings->bAllowJoinViaPresence = true;
			SessionSettings->bAllowJoinViaPresenceFriendsOnly = false;
			SessionSettings->Set(SETTING_MAPNAME, FString("NewMap"), EOnlineDataAdvertisementType::ViaOnlineService);

			// Set the session interface's handle to the 'create session' delegate
			OnCreateSessionCompleteDelegateHandle = SessionInterface->AddOnCreateSessionCompleteDelegate_Handle(OnCreateSessionCompleteDelegate);

			// Create the session
			// The 'create session' delegate will be called here, regardless of the result
			UE_LOG(LogTemp, Warning, TEXT("HostSession()  /  Session will now be created."));
			return SessionInterface->CreateSession(*UserId, SessionName, *SessionSettings);
		} else {
			UE_LOG(LogTemp, Warning, TEXT("HostSession()  /  Failed to create Session. SessionInterface not found or not valid."));
		}
	} else {
		UE_LOG(LogTemp, Warning, TEXT("HostSession()  /  Failed to create Session. OnlineSubsystem not found or not valid."));
	}

	return false;
}


void UTheHazardsGameInstanceSubsystem::OnCreateSessionComplete(FName SessionName, bool WasSuccessful)
{
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Was Session %s Created Successfully: %d"), *SessionName.ToString(), WasSuccessful));
	UE_LOG(LogTemp, Warning, TEXT("OnCreateSessionComplete()  /  Was Session %s Created Successfully: %d"), *SessionName.ToString(), WasSuccessful);

	// Get the OnlineSubsystem
	IOnlineSubsystem* const OnlineSubsystem = IOnlineSubsystem::Get();

	if (OnlineSubsystem) {
		// Get the online subsystem's session interface in order to start a session
		IOnlineSessionPtr SessionInterface = OnlineSubsystem->GetSessionInterface();

		if (SessionInterface.IsValid()) {
			// Clear the 'create session' delegate handle since it's been created
			SessionInterface->ClearOnCreateSessionCompleteDelegate_Handle(OnCreateSessionCompleteDelegateHandle);

			// Assign the 'start session' delegate handle
			OnStartSessionCompleteDelegateHandle = SessionInterface->AddOnStartSessionCompleteDelegate_Handle(OnStartSessionCompleteDelegate);

			// Start the session
			// The 'start session complete' delegate should be called when this is finished
			UE_LOG(LogTemp, Warning, TEXT("OnCreateSessionComplete()  /  Session will now be started."));
			SessionInterface->StartSession(SessionName);
		}
	}
}


void UTheHazardsGameInstanceSubsystem::OnStartSessionComplete(FName SessionName, bool WasSuccessful)
{
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Was Session %s Started Successfully: %d"), *SessionName.ToString(), WasSuccessful));
	UE_LOG(LogTemp, Warning, TEXT("OnStartSessionComplete()  /  Was Session %s Started Successfully: %d"), *SessionName.ToString(), WasSuccessful);

	// Get the OnlineSubsystem
	IOnlineSubsystem* const OnlineSubsystem = IOnlineSubsystem::Get();

	if (OnlineSubsystem) {
		// Get the online subsystem's session interface
		IOnlineSessionPtr SessionInterface = OnlineSubsystem->GetSessionInterface();

		if (SessionInterface.IsValid()) {
			// Clear the 'start session' delegate handle since it's been started
			SessionInterface->ClearOnStartSessionCompleteDelegate_Handle(OnStartSessionCompleteDelegateHandle);
		}
	}

	// If the session was successfully started, we can travel to another map
	// the 'listen' option is necessary for making the host into a listen server
	if (WasSuccessful) {
		UE_LOG(LogTemp, Warning, TEXT("OnStartSessionComplete()  /  Travel to another level"));
		UGameplayStatics::OpenLevel(GetWorld(), "NewMap", true, "listen");
	}
}


void UTheHazardsGameInstanceSubsystem::FindSessions(TSharedPtr<const FUniqueNetId> UserId, bool IsLanMatch, bool IsPresence)
{
	// Get the OnlineSubsystem
	IOnlineSubsystem* const OnlineSubsystem = IOnlineSubsystem::Get();

	if (OnlineSubsystem) {
		// Get the online subsystem's session interface in order to create a session
		IOnlineSessionPtr SessionInterface = OnlineSubsystem->GetSessionInterface();

		if (SessionInterface.IsValid() && UserId.IsValid()) {
			// To-Do: Explain this
			SearchSettings = MakeShareable(new FOnlineSessionSearch());

			// Set the session options
			SearchSettings->bIsLanQuery = IsLanMatch;
			SearchSettings->MaxSearchResults = 20;
			SearchSettings->PingBucketSize = 50;

			// This option enables searching for hosts who have enabled Presence
			if (IsPresence) {
				SearchSettings->QuerySettings.Set(SEARCH_PRESENCE, IsPresence, EOnlineComparisonOp::Equals);
			}

			// To-Do: Explain this
			TSharedRef<FOnlineSessionSearch> SearchSettingsRef = SearchSettings.ToSharedRef();

			// Assign the 'find session' delegate handle
			OnFindSessionsCompleteDelegateHandle = SessionInterface->AddOnFindSessionsCompleteDelegate_Handle(OnFindSessionsCompleteDelegate);

			// Begin finding sessions
			// The delegate will be triggered once the search is finished
			UE_LOG(LogTemp, Warning, TEXT("FindSessions()  /  Begin searching for sessions"));
			SessionInterface->FindSessions(*UserId, SearchSettingsRef);
		}
	} else {

	}
}


void UTheHazardsGameInstanceSubsystem::OnFindSessionsComplete(bool WasSuccessful)
{
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Were Sessions Found Successfully: %d"), WasSuccessful));
	UE_LOG(LogTemp, Warning, TEXT("OnFindSessionsComplete()  /  Were Sessions Found Successfully: %d"), WasSuccessful);

	// Get the OnlineSubsystem
	IOnlineSubsystem* const OnlineSubsystem = IOnlineSubsystem::Get();

	if (OnlineSubsystem) {
		// Get the online subsystem's session interface
		IOnlineSessionPtr SessionInterface = OnlineSubsystem->GetSessionInterface();

		if (SessionInterface.IsValid()) {
			// Clear the 'find session' delegate handle since the search has finished
			SessionInterface->ClearOnFindSessionsCompleteDelegate_Handle(OnFindSessionsCompleteDelegateHandle);

			// Quickly display the number of sessions found
			// To-Do: Delete this once proper UI is implemented
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Number of Sessions Found: %d"), SearchSettings->SearchResults.Num()));
			UE_LOG(LogTemp, Warning, TEXT("OnFindSessionsComplete()  /  Were Sessions Found Successfully: %d"), WasSuccessful);

			// To-Do: Create UI for finding sessions
			if (SearchSettings->SearchResults.Num() > 0) {
				// SearchSettings->SearchResults is an array that holds any found Sessions
				for (int i = 0; i < SearchSettings->SearchResults.Num(); i++) {
					// To-Do: Remove this when UI is done
					GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Session Number: %d | Sessionname: %s "), i + 1, *(SearchSettings->SearchResults[i].Session.OwningUserName)));
				}
			}
		}
	}
}


bool UTheHazardsGameInstanceSubsystem::JoinSession(TSharedPtr<const FUniqueNetId> UserId, FName SessionName, const FOnlineSessionSearchResult& SearchResult)
{
	// Get the OnlineSubsystem
	IOnlineSubsystem* const OnlineSubsystem = IOnlineSubsystem::Get();

	if (OnlineSubsystem) {
		// Get the online subsystem's session interface
		IOnlineSessionPtr SessionInterface = OnlineSubsystem->GetSessionInterface();

		if (SessionInterface.IsValid() && UserId.IsValid()) {
			// assign the delegate handle
			OnJoinSessionCompleteDelegateHandle = SessionInterface->AddOnJoinSessionCompleteDelegate_Handle(OnJoinSessionCompleteDelegate);

			// Attempt to join the session
			// Pass the session reference
			return SessionInterface->JoinSession(*UserId, SessionName, SearchResult);
		}
	}

	return false;
}


void UTheHazardsGameInstanceSubsystem::OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result)
{

}