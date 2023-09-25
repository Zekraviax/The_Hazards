#pragma once


#include "CoreMinimal.h"

#include "GameFramework/SaveGame.h"
#include "TheHazardsVariables.h"

#include "SaveGameOptions.generated.h"


class UWidgetMenuOptions;


UCLASS()
class THEHAZARDS_API USaveGameOptions : public USaveGame
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString PlayerDataSaveFilePath = "C:\\users\\zekra\\documents\\My Games\\The Hazards\\zekra";

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FOptionsData OptionsData;

	UFUNCTION(BlueprintCallable)
	void SaveOptionsToJson(FOptionsData InOptionsData, FString PlayerName);
};