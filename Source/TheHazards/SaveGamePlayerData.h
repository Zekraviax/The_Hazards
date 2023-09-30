#pragma once


#include "CoreMinimal.h"

#include "GameFramework/SaveGame.h"
#include "TheHazardsVariables.h"

#include "SaveGamePlayerData.generated.h"


class AEntityBaseCharacter;


UCLASS()
class THEHAZARDS_API USaveGamePlayerData : public USaveGame
{
	GENERATED_BODY()

public:
	// To-Do: Put this variable somewhere global, so it can easily be changed and accessed
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString PlayerDataSaveFilePath = "C:\\users\\zekra\\documents\\My Games\\The Hazards\\zekra";

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FEntityBaseData PlayerData;

	UPROPERTY()
	AEntityBaseCharacter* PlayerEntityReference;

	UFUNCTION(BlueprintCallable)
	void SavePlayerDataToJson();

	UFUNCTION(BlueprintCallable)
	void LoadPlayerDataFromJson(AEntityBaseCharacter* PlayerEntity, FString PlayerSaveDataFolderName);
};