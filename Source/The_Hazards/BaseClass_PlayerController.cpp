// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseClass_PlayerController.h"

ABaseClass_PlayerController::ABaseClass_PlayerController()
{

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