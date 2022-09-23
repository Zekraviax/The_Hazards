#include "EntityPlayerCharacter.h"


#include "WidgetHudBattle.h"
#include "WidgetMenuFindSessions.h"
#include "WidgetMenuHostSession.h"
#include "WidgetMenuMultiplayer.h"
#include "WidgetMenuPause.h"


//////////////////////////////////////////////////////////////////////////
// Input
void AEntityPlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AEntityBaseCharacter::OnJumpBegin);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Bind fire event
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AEntityBaseCharacter::OnFire);

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &AEntityBaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AEntityBaseCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &AEntityBaseCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
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
}


void AEntityPlayerCharacter::PauseGame()
{
	// To-Do: Prevent players from pausing when at the main menu

	// Tell the controller to open the pause menu
	//GetTheHazardsPlayerController()->OpenWidgetByClass(GetTheHazardsPlayerController()->WidgetMenuPauseClass);

	// Open new widget based on closed widget
	if (GetTheHazardsPlayerController()->CurrentOpenWidgetClass == GetTheHazardsPlayerController()->WidgetHudBattleClass) {
		// If the HUD is on-screen, that must mean the game is unpaused
		GetTheHazardsPlayerController()->OpenWidgetByClass(GetTheHazardsPlayerController()->WidgetMenuPauseClass);
	} else if (GetTheHazardsPlayerController()->CurrentOpenWidgetClass == GetTheHazardsPlayerController()->WidgetMenuPauseClass) {
		// If the pause menu is on-screen, then unpause the game and display the HUD again
		GetTheHazardsPlayerController()->OpenWidgetByClass(GetTheHazardsPlayerController()->WidgetHudBattleClass);
	} else if (GetTheHazardsPlayerController()->CurrentOpenWidgetClass == GetTheHazardsPlayerController()->WidgetMenuMultiplayerClass) {
		// If the multiplayer menu is on-screen, return to the main pause menu
		GetTheHazardsPlayerController()->OpenWidgetByClass(GetTheHazardsPlayerController()->WidgetMenuPauseClass);
	} else if (GetTheHazardsPlayerController()->CurrentOpenWidgetClass == GetTheHazardsPlayerController()->WidgetMenuHostSessionClass) {
		// If the 'create host session' menu is on-screen, go back to the main multiplayer menu
		GetTheHazardsPlayerController()->OpenWidgetByClass(GetTheHazardsPlayerController()->WidgetMenuMultiplayerClass);
	} else if (GetTheHazardsPlayerController()->CurrentOpenWidgetClass == GetTheHazardsPlayerController()->WidgetMenuFindSessionsClass) {
		// If the 'create host session' menu is on-screen, go back to the main multiplayer menu
		GetTheHazardsPlayerController()->OpenWidgetByClass(GetTheHazardsPlayerController()->WidgetMenuMultiplayerClass);
	}
}