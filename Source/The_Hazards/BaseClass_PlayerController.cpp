// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseClass_PlayerController.h"

ABaseClass_PlayerController::ABaseClass_PlayerController()
{

}

void ABaseClass_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Mouse Input
	//bShowMouseCursor = true;
	SetInputMode(FInputModeGameAndUI());
}