#pragma once


#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TheHazardsPlayerController.generated.h"


class AEntityBaseCharacter;
class UWidgetHudBattle;
class UWidgetMenuFindSessions;
class UWidgetMenuHostSession;
class UWidgetMenuMultiplayer;
class UWidgetMenuPause;
class UWidgetSessionListEntry;


UCLASS()
class THEHAZARDS_API ATheHazardsPlayerController : public APlayerController
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

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Interface)
	//UWidgetSessionListEntry* WidgetSessionListEntryReference;

	// Use the variable to track what widgets need to be opened when one is closed
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Interface)
	TSubclassOf<UUserWidget> CurrentOpenWidgetClass;

	// Use this function to create widgets for the first and only time
	virtual void OnPossess(APawn* InPawn) override;

	// Return this controller's pawn, cast as an EntityBaseCharacter
	AEntityBaseCharacter* GetPawnAsEntityBaseCharacter();

	// Loop through all valid widgets, opening the designated widget and closing all others
	UFUNCTION()
	void OpenWidgetByClass(TSubclassOf<UUserWidget> WidgetClass);
};