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
};
