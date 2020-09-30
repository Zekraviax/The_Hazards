#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "SaveFile_MetaList.generated.h"


UCLASS()
class THE_HAZARDS_API USaveFile_MetaList : public USaveGame
{
	GENERATED_BODY()
	
public:
// Base Variables
// --------------------------------------------------

// ------------------------- Save Data
	UPROPERTY()
	TArray<FString> SaveFileNames;

	UPROPERTY()
	TMap<FString, FString> SaveFileAndLevelNames;

	UPROPERTY()
	int TotalManualSaveCount;

// Save/Load Functions
// --------------------------------------------------
	UFUNCTION()
	void SaveGameDelegateFunction(const FString& SlotName, const int32 UserIndex, bool bSuccess);

	UFUNCTION()
	void LoadGameDelegateFunction(const FString& SlotName, const int32 UserIndex, USaveGame* LoadedData);
};
