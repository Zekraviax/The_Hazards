#pragma once


#include "CoreMinimal.h"
#include "EntityBaseCharacter.h"
#include "EntityPlayerCharacter.generated.h"


class AActorInteractable;
class UWidgetDialogue;
class UWidgetHudBattle;
class UWidgetMenuCraftingWindow;
class UWidgetMenuDeveloper;
class UWidgetMenuFindSessions;
class UWidgetMenuHostSession;
class UWidgetMenuInventory;
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

	// Classes

	// Used to add the widget to the players' screen whenever their character is spawned
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Interface)
	TSubclassOf<UWidgetDialogue> WidgetDialogueClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Interface)
	TSubclassOf<UWidgetHudBattle> WidgetHudBattleClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Interface)
	TSubclassOf<UWidgetMenuCraftingWindow> WidgetMenuCraftingWindowClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Interface)
	TSubclassOf<UWidgetMenuDeveloper> WidgetMenuDeveloperClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Interface)
	TSubclassOf<UWidgetMenuFindSessions> WidgetMenuFindSessionsClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Interface)
	TSubclassOf<UWidgetMenuHostSession> WidgetMenuHostSessionClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Interface)
	TSubclassOf<UWidgetMenuInventory> WidgetMenuInventoryClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Interface)
	TSubclassOf<UWidgetMenuMultiplayer> WidgetMenuMultiplayerClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Interface)
	TSubclassOf<UWidgetMenuPause> WidgetMenuPauseClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Interface)
	TSubclassOf<UWidgetSessionListEntry> WidgetSessionListEntryClass;

	// References
	// Keep a reference to the widget itself so we can show and hide it instead of creating and destroying it every time
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Interface)
	UWidgetDialogue* WidgetDialogueReference;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Interface)
	UWidgetHudBattle* WidgetHudBattleReference;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Interface)
	UWidgetMenuCraftingWindow* WidgetMenuCraftingWindowReference;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Interface)
	UWidgetMenuDeveloper* WidgetMenuDeveloperReference;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Interface)
	UWidgetMenuFindSessions* WidgetMenuFindSessionsReference;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Interface)
	UWidgetMenuHostSession* WidgetMenuHostSessionReference;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Interface)
	UWidgetMenuInventory* WidgetMenuInventoryReference;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Interface)
	UWidgetMenuMultiplayer* WidgetMenuMultiplayerReference;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Interface)
	UWidgetMenuPause* WidgetMenuPauseReference;

	// Use the variable to track what widgets need to be opened when one is closed
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Interface)
	TSubclassOf<UUserWidget> CurrentOpenWidgetClass;

	// Save a reference to the actor we're currently looking at so we can interact with it if it's within range
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gameplay)
	AActor* LookAtInteractableActor;

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Client side function that creates widgets and adds the HUD to the player's viewport
	UFUNCTION(Client, Reliable, BlueprintCallable)
	void ClientCreateWidgets();

	// Pause the game and open the pause menu, or
	// Close one menu and open another related menu
	void PauseGame();

	// Open the dev menu
	// Or close the dev menu and return the HUD
	UFUNCTION()
	void OpenDevMenu();

	// Open or close the inventory and return the HUD
	UFUNCTION()
	void OpenInventory();

	UFUNCTION()
	void OpenCraftingWindow();

	UFUNCTION()
	void OpenDialogue();

	// Loop through all valid widgets, opening the designated widget and closing all others
	UFUNCTION()
	void OpenWidgetByClass(TSubclassOf<UUserWidget> WidgetClass);

	// Attempt to interact with an entity
	UFUNCTION()
	void OnInteract();
};