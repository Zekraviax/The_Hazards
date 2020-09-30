#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"

#include "TheHazards_GameMode.h"
#include "Misc/DateTime.h"

#include "SaveFile_Slot.generated.h"

// Forward Declarations
class AEntity_Player;
class AEntity_EnemyNPC;
class UTheHazards_GameInstance;


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
	FString LevelName;

	UPROPERTY()
	AEntity_Player* PlayerReference;

	UPROPERTY()
	TArray<AEntity_EnemyNPC*> EnemyReferencesArray;

	UPROPERTY()
	UTheHazards_GameInstance* GameInstanceReference;

	//UPROPERTY()
	//FAsyncSaveGameToSlotDelegate SaveDelegateReference;

// Level Variables
// --------------------------------------------------

// ------------------------- Entities

	
// ------------------------- Level


// Save/Load Functions
// --------------------------------------------------
	UFUNCTION()
	void SaveGameDelegateFunction(const FString& SlotName, const int32 UserIndex, bool bSuccess);

	UFUNCTION()
	void LoadGameDelegateFunction(const FString& SlotName, const int32 UserIndex, USaveGame* LoadedGameData);

	//UFUNCTION()
	//void ReturnSaveGameDelegateFunction(const FString& SlotName, const int32 UserIndex, bool bSuccess);
};
