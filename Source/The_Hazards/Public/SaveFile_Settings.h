#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"

#include "TheHazards_GameMode.h"
#include "Containers/EnumAsByte.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerInput.h"
#include "Runtime/Engine/Classes/GameFramework/InputSettings.h"
#include "Runtime/CoreUObject/Public/UObject/UObjectGlobals.h"

#include "SaveFile_Settings.generated.h"


UCLASS()
class THE_HAZARDS_API USaveFile_Settings : public USaveGame
{
	GENERATED_BODY()
	
public:
// Constructor

// Settings Variables
// --------------------------------------------------

// ------------------------- Audio Settings
	UPROPERTY()
	bool MuteSoundOverride;

	UPROPERTY()
	float MasterVolume;

	UPROPERTY()
	float MusicVolume;

	UPROPERTY()
	float EffectsVolume;

	UPROPERTY()
	float AmbienceVolume;

// ------------------------- Video Settings
	UPROPERTY()
	FVector2D ScreenResolution;

	UPROPERTY()
	TEnumAsByte<EWindowMode::Type> FullscreenMode;

	UPROPERTY()
	bool VSyncEnabled;

// ------------------------- Controls Settings
	UPROPERTY()
	FInputAxisKeyMapping MoveForwardKey;

	UPROPERTY()
	FInputAxisKeyMapping MoveBackwardKey;

// ------------------------- Keybinds Settings
};
