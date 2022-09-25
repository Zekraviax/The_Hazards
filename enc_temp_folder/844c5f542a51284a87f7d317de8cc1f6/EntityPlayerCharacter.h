#pragma once


#include "CoreMinimal.h"
#include "EntityBaseCharacter.h"
#include "EntityPlayerCharacter.generated.h"


class UWidgetHudBattle;
class UWidgetMenuFindSessions;
class UWidgetMenuHostSession;
class UWidgetMenuMultiplayer;
class UWidgetMenuPause;
class UWidgetSessionListEntry;


UCLASS()
class THEHAZARDS_API AEntityPlayerCharacter : public AEntityBaseCharacter
{
	GENERATED_BODY()


public:
	// Array of widgets that can be added to a user's screen
	// We use this array to close all other widgets when one is opened
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Interface)
	TArray<UUserWidget*> ValidWidgets;

	// Used to add the widget to the players' screen whenever their character is spawned
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Interface)
	TSubclassOf<UWidgetHudBattle> WidgetHudBattleClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Interface)
	TSubclassOf<UWidgetMenuFindSessions> WidgetMenuFindSessionsClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Interface)
	TSubclassOf<UWidgetMenuHostSession> WidgetMenuHostSessionClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Interface)
	TSubclassOf<UWidgetMenuMultiplayer> WidgetMenuMultiplayerClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Interface)
	TSubclassOf<UWidgetMenuPause> WidgetMenuPauseClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Interface)
	TSubclassOf<UWidgetSessionListEntry> WidgetSessionListEntryClass;

	// Keep a reference to the widget itself so we can show and hide it instead of creating and destroying it every time
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Interface)
	UWidgetHudBattle* WidgetHudBattleReference;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Interface)
	UWidgetMenuFindSessions* WidgetMenuFindSessionsReference;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Interface)
	UWidgetMenuHostSession* WidgetMenuHostSessionReference;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Interface)
	UWidgetMenuMultiplayer* WidgetMenuMultiplayerReference;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Interface)
	UWidgetMenuPause* WidgetMenuPauseReference;

	// Use the variable to track what widgets need to be opened when one is closed
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Interface)
	TSubclassOf<UUserWidget> CurrentOpenWidgetClass;


protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface


public:
	// Pause the game and open the pause menu, or
	// Close one menu and open another related menu
	void PauseGame();

	// Server sends this function to tell a client to create widgets
	UFUNCTION(Server, Unreliable)
	void ServerCreateWidgets();

	// Client side function that creates widgets and adds the HUD to the player's viewport
	UFUNCTION(Client, Unreliable)
	void ClientCreateWidgets();

	// Loop through all valid widgets, opening the designated widget and closing all others
	UFUNCTION()
	void OpenWidgetByClass(TSubclassOf<UUserWidget> WidgetClass);
};