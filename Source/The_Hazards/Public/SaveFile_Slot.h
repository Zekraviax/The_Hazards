#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"

#include "TheHazards_GameMode.h"

#include "SaveFile_Slot.generated.h"


UCLASS()
class THE_HAZARDS_API USaveFile_Slot : public USaveGame
{
	GENERATED_BODY()

public:
// Constructor

// Slot Variables
// --------------------------------------------------
	UPROPERTY()
	FString SlotName;

// Player Variables
// --------------------------------------------------

// ------------------------- Character
	UPROPERTY()
	F_Entity_CharacterSheet CharacterSheet;

	UPROPERTY()
	int32 Level;

	UPROPERTY()
	int32 Experience;

	UPROPERTY()
	int32 Money;

	UPROPERTY()
	int32 Scrap;
	
// ------------------------- Level
};
