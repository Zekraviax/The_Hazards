// Copyright Epic Games, Inc. All Rights Reserved.

#include "TheHazardsGameMode.h"
#include "TheHazardsHUD.h"
#include "TheHazardsCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATheHazardsGameMode::ATheHazardsGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ATheHazardsHUD::StaticClass();
}
