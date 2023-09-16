#include "EntityPlayerCharacter.h"


#include "ActorComponentBaseStats.h"
#include "ActorInteractable.h"
#include "Camera/CameraComponent.h"
#include "InterfaceInteractions.h"
#include "Kismet/GameplayStatics.h"
#include "WidgetHudBattle.h"
#include "WidgetMenuCraftingWindow.h"
#include "WidgetMenuDeveloper.h"
#include "WidgetMenuFindSessions.h"
#include "WidgetMenuHostSession.h"
#include "WidgetMenuInventory.h"
#include "WidgetMenuMultiplayer.h"
#include "WidgetMenuPause.h"


void AEntityPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Line trace to find the actor/object the entity is directly looking at
	FHitResult Hit;

	FVector TraceStart = FirstPersonCameraComponent->GetComponentLocation();
	FVector TraceEnd = FirstPersonCameraComponent->GetComponentLocation() + FirstPersonCameraComponent->GetForwardVector() * 10000.0f;
	UKismetSystemLibrary::LineTraceSingle(this, TraceStart, TraceEnd, UEngineTypes::ConvertToTraceType(ECC_Camera), false, ActorsToIgnore, EDrawDebugTrace::ForOneFrame, Hit, true);


	if (Hit.Actor.Get() == NULL && LookAtInteractableActor != NULL) {
		LookAtInteractableActor = NULL;
	} else if (Hit.Actor.Get() != LookAtInteractableActor) {
		// Check if the 'look at' actor implements the interact interface
		if (Cast<IInterfaceInteractions>(Hit.Actor.Get())) {
			LookAtInteractableActor = Hit.Actor.Get();
		}
	}
}


//////////////////////////////////////////////////////////////////////////
// Input
void AEntityPlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AEntityBaseCharacter::OnJumpBegin);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Bind attack events
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AEntityBaseCharacter::OnFire);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &AEntityBaseCharacter::OnStopFiring);
	PlayerInputComponent->BindAction("SpecialAttack", IE_Pressed, this, &AEntityBaseCharacter::OnLaunchSpecialAttack);

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &AEntityBaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AEntityBaseCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &AEntityBaseCharacter::EntityAddYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AEntityBaseCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &AEntityBaseCharacter::EntityAddPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AEntityBaseCharacter::LookUpAtRate);

	// Begin and end crouching
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AEntityBaseCharacter::OnCrouchBegin);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &AEntityBaseCharacter::OnCrouchEnd);

	// Begin and end sprinting
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &AEntityBaseCharacter::OnSprintBegin);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &AEntityBaseCharacter::OnSprintEnd);

	// To-Do: Add binds for escape key to both:
	// Open pause menu
	// Close current menu and open a related menu
	PlayerInputComponent->BindAction("PauseGame", IE_Released, this, &AEntityPlayerCharacter::PauseGame).bExecuteWhenPaused = true;

	// Open or close the dev menu
	// When closing, return the HUD to the player's viewport
	PlayerInputComponent->BindAction("DevMenu", IE_Released, this, &AEntityPlayerCharacter::OpenDevMenu).bExecuteWhenPaused = true;

	// Interact with entities in the world
	PlayerInputComponent->BindAction("Interact", IE_Released, this, &AEntityPlayerCharacter::OnInteract);

	// Open or close the inventory
	PlayerInputComponent->BindAction("Inventory", IE_Released, this, &AEntityPlayerCharacter::OpenInventory).bExecuteWhenPaused = true;

	PlayerInputComponent->BindAction("CraftingWindow", IE_Released, this, &AEntityPlayerCharacter::OpenCraftingWindow).bExecuteWhenPaused = true;
}


void AEntityPlayerCharacter::PauseGame()
{
	// To-Do: Prevent players from pausing when at the main menu

	// Open new widget based on closed widget
	if (CurrentOpenWidgetClass == WidgetHudBattleClass) {
		// If the HUD is on-screen, that must mean the game is unpaused
		OpenWidgetByClass(WidgetMenuPauseClass);
	} else if (CurrentOpenWidgetClass == WidgetMenuPauseClass) {
		// If the pause menu is on-screen, then unpause the game and display the HUD again
		OpenWidgetByClass(WidgetHudBattleClass);
	} else if (CurrentOpenWidgetClass == WidgetMenuMultiplayerClass) {
		// If the multiplayer menu is on-screen, return to the main pause menu
		OpenWidgetByClass(WidgetMenuPauseClass);
	} else if (CurrentOpenWidgetClass == WidgetMenuHostSessionClass) {
		// If the 'create host session' menu is on-screen, go back to the main multiplayer menu
		OpenWidgetByClass(WidgetMenuMultiplayerClass);
	} else if (CurrentOpenWidgetClass == WidgetMenuFindSessionsClass) {
		// If the 'create host session' menu is on-screen, go back to the main multiplayer menu
		OpenWidgetByClass(WidgetMenuMultiplayerClass);
	}
}


void AEntityPlayerCharacter::ClientCreateWidgets_Implementation()
{
	UE_LOG(LogTemp, Warning, TEXT("ClientCreateWidgets_Implementation()  /  Execute function call from server"));

	// Create the player's HUD
	if (WidgetHudBattleClass && !WidgetHudBattleReference) {
		WidgetHudBattleReference = CreateWidget<UWidgetHudBattle>(GetWorld(), WidgetHudBattleClass);

		// Set HUD variables for the first time
		WidgetHudBattleReference->UpdateHealthPointsInHud(GetBaseStatsComponent()->CurrentHealthPoints, GetBaseStatsComponent()->MaximumHealthPoints);
		WidgetHudBattleReference->UpdateAuraPointsInHud(GetBaseStatsComponent()->CurrentAuraPoints, GetBaseStatsComponent()->MaximumAuraPoints);
		WidgetHudBattleReference->UpdateLevelInHud(GetBaseStatsComponent()->Level);
		WidgetHudBattleReference->UpdateExperiencePointsInHud(GetBaseStatsComponent()->CurrentExperiencePoints);
		WidgetHudBattleReference->UpdateCreditsInHud(GetBaseStatsComponent()->Credits);
		WidgetHudBattleReference->UpdateScrapInHud(GetBaseStatsComponent()->Scrap);

		WidgetHudBattleReference->AddToPlayerScreen();
		CurrentOpenWidgetClass = WidgetHudBattleClass;

		ValidWidgets.Add(WidgetHudBattleReference);
	}

	if (WidgetMenuDeveloperClass && !WidgetMenuDeveloperReference) {
		WidgetMenuDeveloperReference = CreateWidget<UWidgetMenuDeveloper>(GetWorld(), WidgetMenuDeveloperClass);

		ValidWidgets.Add(WidgetMenuDeveloperReference);
	}

	// Create the multiplayer menus
	if (WidgetMenuFindSessionsClass && !WidgetMenuFindSessionsReference) {
		WidgetMenuFindSessionsReference = CreateWidget<UWidgetMenuFindSessions>(GetWorld(), WidgetMenuFindSessionsClass);

		ValidWidgets.Add(WidgetMenuFindSessionsReference);
	}

	if (WidgetMenuMultiplayerClass && !WidgetMenuMultiplayerReference) {
		WidgetMenuMultiplayerReference = CreateWidget<UWidgetMenuMultiplayer>(GetWorld(), WidgetMenuMultiplayerClass);

		ValidWidgets.Add(WidgetMenuMultiplayerReference);
	}

	if (WidgetMenuHostSessionClass && !WidgetMenuHostSessionReference) {
		WidgetMenuHostSessionReference = CreateWidget<UWidgetMenuHostSession>(GetWorld(), WidgetMenuHostSessionClass);

		ValidWidgets.Add(WidgetMenuHostSessionReference);
	}

	// Create the in-game pause menu
	if (WidgetMenuPauseClass && !WidgetMenuPauseReference) {
		WidgetMenuPauseReference = CreateWidget<UWidgetMenuPause>(GetWorld(), WidgetMenuPauseClass);

		ValidWidgets.Add(WidgetMenuPauseReference);
	}

	// Create other menus
	if (WidgetMenuInventoryClass && !WidgetMenuInventoryReference) {
		WidgetMenuInventoryReference = CreateWidget<UWidgetMenuInventory>(GetWorld(), WidgetMenuInventoryClass);
		WidgetMenuInventoryReference->OwningEntityInventoryComponent = GetInventoryComponent();

		ValidWidgets.Add(WidgetMenuInventoryReference);
	}

	if (WidgetMenuCraftingWindowClass && !WidgetMenuCraftingWindowReference) {
		WidgetMenuCraftingWindowReference = CreateWidget<UWidgetMenuCraftingWindow>(GetWorld(), WidgetMenuCraftingWindowClass);

		// To-do: Figure out why this line causes the game to crash when inspecting the player BP while playing-in-editor
		WidgetMenuCraftingWindowReference->OwningEntityInventoryComponent = GetInventoryComponent();

		ValidWidgets.Add(WidgetMenuCraftingWindowReference);
	}

	// Set the input mode
	GetTheHazardsPlayerController()->SetInputMode(FInputModeGameOnly());
}


void AEntityPlayerCharacter::OpenDevMenu()
{
	if (CurrentOpenWidgetClass != WidgetMenuDeveloperClass) {
		OpenWidgetByClass(WidgetMenuDeveloperClass);
	} else {
		OpenWidgetByClass(WidgetHudBattleClass);
	}
}


void AEntityPlayerCharacter::OpenInventory()
{
	if (CurrentOpenWidgetClass != WidgetMenuInventoryClass) {
		OpenWidgetByClass(WidgetMenuInventoryClass);
	} else {
		OpenWidgetByClass(WidgetHudBattleClass);
	}
}


void AEntityPlayerCharacter::OpenCraftingWindow()
{
	if (CurrentOpenWidgetClass != WidgetMenuCraftingWindowClass) {
		OpenWidgetByClass(WidgetMenuCraftingWindowClass);
	} else {
		OpenWidgetByClass(WidgetHudBattleClass);
	}
}


void AEntityPlayerCharacter::OpenWidgetByClass(TSubclassOf<UUserWidget> WidgetClass)
{
	for (UUserWidget* Widget : ValidWidgets) {
		if (Widget->GetClass() == WidgetClass) {
			Widget->AddToViewport();
			CurrentOpenWidgetClass = WidgetClass;
		} else {
			Widget->RemoveFromViewport();
		}
	}

	// To-Do: Activate special functions based on which widget has been added to the viewport

	// Show or hide the cursor
	// Change input modes based on whether or not the current widget on-screen is the HUD
	if (WidgetClass == WidgetHudBattleClass) {
		GetTheHazardsPlayerController()->bShowMouseCursor = false;
		GetTheHazardsPlayerController()->SetInputMode(FInputModeGameOnly());

		UGameplayStatics::SetGamePaused(GetWorld(), false);
	} else {
		GetTheHazardsPlayerController()->bShowMouseCursor = true;
		GetTheHazardsPlayerController()->SetInputMode(FInputModeGameAndUI());

		UGameplayStatics::SetGamePaused(GetWorld(), true);
	}

	// Dev Menu: populate the widgets with the player's data
	if (WidgetClass == WidgetMenuDeveloperClass) {
		WidgetMenuDeveloperReference->PopulateEditableTextBoxes();
	}

	// Find Sessions
	if (WidgetClass == WidgetMenuFindSessionsClass) {
		WidgetMenuFindSessionsReference->BeginSearchForSessions();
	}

	// Populate the inventory with the player's items
	if (WidgetClass == WidgetMenuInventoryClass) {
		WidgetMenuInventoryReference->PopulateUnequippedItemsScrollBox(GetInventoryComponent());
		WidgetMenuInventoryReference->PopulateEquippedItemsScrollBox(GetInventoryComponent());
	}

	if (WidgetClass == WidgetMenuCraftingWindowClass) {
		WidgetMenuCraftingWindowReference->PopulateScrollBoxes();
	}
}


void AEntityPlayerCharacter::OnInteract()
{
	if (LookAtInteractableActor != NULL) {
		if (Cast<IInterfaceInteractions>(LookAtInteractableActor)) {
			// To-Do: Check if entity is overlapping with the lookat actor's box collision component
			//TArray<AActor*> OverlappingActors;
			//GetOverlappingActors(OverlappingActors, AActor::StaticClass());

			//if (OverlappingActors.Contains(LookAtInteractableActor)) {
			Cast<IInterfaceInteractions>(LookAtInteractableActor)->Execute_OnInteract(LookAtInteractableActor);
			//}
		}
	}
}