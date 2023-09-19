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
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString PlayerDataSaveFilePath = "C:\\users\\zekra\\documents\\My Games\\The Hazards\\zekra";

	UFUNCTION(BlueprintCallable)
	void SavePlayerDataToJson(AEntityBaseCharacter* PlayerEntity);

	UFUNCTION(BlueprintCallable)
	void LoadPlayerDataFromJson(AEntityBaseCharacter* PlayerEntity, FString PlayerSaveDataFolderName);
};