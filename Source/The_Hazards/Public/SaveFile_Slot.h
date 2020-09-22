#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"

#include "TheHazards_GameMode.h"
#include "Misc/DateTime.h"

#include "SaveFile_Slot.generated.h"

// Forward Declarations
class AEntity_Player;
class AEntity_EnemyNPC;


UCLASS()
class THE_HAZARDS_API USaveFile_Slot : public USaveGame
{
	GENERATED_BODY()

public:
// Constructor

// Slot Variables
// --------------------------------------------------
	UPROPERTY()
	FText SaveSlotName;

	UPROPERTY()
	FDateTime DateSaved;

	UPROPERTY()
	int SlotNumber;

	UPROPERTY()
	int CurrentTotalManualSaveCount;

// ------------------------- References
	UPROPERTY()
	AEntity_Player* PlayerReference;

	UPROPERTY()
	TArray<AEntity_EnemyNPC*> EnemyReferencesArray;

// Level Variables
// --------------------------------------------------

// ------------------------- Entities

	
// ------------------------- Level


// Save/Load Functions
// --------------------------------------------------
	UFUNCTION()
	void SaveGameDelegateFunction(const FString& SlotName, const int32 UserIndex, bool bSuccess);
};
