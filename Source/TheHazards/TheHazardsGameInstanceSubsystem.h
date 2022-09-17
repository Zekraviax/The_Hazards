#pragma once


#include "CoreMinimal.h"

#include "Interfaces/OnlineSessionInterface.h"
#include "Subsystems/GameInstanceSubsystem.h"

#include "TheHazardsGameInstanceSubsystem.generated.h"


UCLASS()
class THEHAZARDS_API UTheHazardsGameInstanceSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

		// This subsystem is used for handling multiplayer functions such as hosting sessions

public:
	// Constructor
	UTheHazardsGameInstanceSubsystem(const FObjectInitializer& ObjectInitializer);

	/** Begin hosting a multiplayer session
	*
	* @param UserId			The unique ID of the player who is hosting the session
	* @param SessionName	Name of the session as chosen by the host
	* @param IsLanMatch		Whether or not this session is a LAN match
	* @param IsPresence		Whether or not this session is a Presence session
	* @param MaxNumPlayers	The maximum number of players allowed to connect to the session
	*/
	bool HostSession(TSharedPtr<const FUniqueNetId> UserId, FName SessionName, bool IsLanMatch, bool IsPresence, int32 MaxNumPlayers);


	// Delegate that is called when a session is completed
	FOnCreateSessionCompleteDelegate OnCreateSessionCompleteDelegate;

	// Handle for the 'create session' delegate
	FDelegateHandle OnCreateSessionCompleteDelegateHandle;

	/** This function is called when a session is created
	*
	* @param SessionName	Name of the session as chosen by the host
	* @param WasSuccessful	Whether or not the session was created successfully
	*/
	virtual void OnCreateSessionComplete(FName SessionName, bool WasSuccessful);


	// Delegate that is called when a session is started
	FOnStartSessionCompleteDelegate OnStartSessionCompleteDelegate;

	// Handle for the 'start session' delegate
	FDelegateHandle OnStartSessionCompleteDelegateHandle;

	// Variable for saving a user's session options
	TSharedPtr<class FOnlineSessionSettings> SessionSettings;

	/** This function is called when a session is started
	*
	* @param SessionName	Name of the session as chosen by the host
	* @param WasSuccessful	Whether or not the session was started successfully
	*/
	virtual void OnStartSessionComplete(FName SessionName, bool WasSuccessful);


	/** Begin hosting a multiplayer session
	*
	* @param UserId			The unique ID of the player who is hosting the session
	* @param IsLanMatch		Whether or not we're searching for LAN sessions
	* @param IsPresence		Whether or not we're searching for Presence session
	*/
	void FindSessions(TSharedPtr<const FUniqueNetId> UserId, bool IsLanMatch, bool IsPresence);

	// Delegate that is called when sessions are found
	FOnFindSessionsCompleteDelegate OnFindSessionsCompleteDelegate;

	// Handle for the 'find sessions' delegate
	FDelegateHandle OnFindSessionsCompleteDelegateHandle;

	// Variable for saving a user's search options
	TSharedPtr<class FOnlineSessionSearch> SearchSettings;

	/** This function is called when the search for sessions has finished
	*
	* @param WasSuccessful	Whether or not the search had any errors
	*/
	void OnFindSessionsComplete(bool WasSuccessful);


	/** Join the given session
	*
	* @param UserId			The unique ID of the player who is hosting the session
	* @param SessionName	Name of the session that we wish to join
	* @param SearchResult	Reference to the session
	*/
	bool JoinSession(TSharedPtr<const FUniqueNetId> UserId, FName SessionName, const FOnlineSessionSearchResult& SearchResult);

	// Delegate that is called when a session is joined
	FOnJoinSessionCompleteDelegate OnJoinSessionCompleteDelegate;

	// Handle for the 'join sessions' delegate
	FDelegateHandle OnJoinSessionCompleteDelegateHandle;

	/** This function is called when a session has been successfully joined
	*
	* @param SessionName	The name of the session that was joined
	* @param Result			The result of the attempt to join a session
	*/
	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);
};