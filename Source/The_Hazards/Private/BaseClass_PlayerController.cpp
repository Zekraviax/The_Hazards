#include "BaseClass_PlayerController.h"

#include "BaseClass_Widget_Options.h"
#include "BaseClass_Widget_MainMenu.h"
#include "BaseClass_Widget_SaveLoad.h"


ABaseClass_PlayerController::ABaseClass_PlayerController()
{
	MainMenuMode = true;
}

void ABaseClass_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Mouse Input
	FInputModeGameAndUI InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockOnCapture);
	InputMode.SetHideCursorDuringCapture(true);
	SetInputMode(InputMode);
}