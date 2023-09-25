#pragma once


#include "CoreMinimal.h"

#include "Engine/GameInstance.h"
#include "SaveGameOptions.h"

#include "TheHazardsGameInstance.generated.h"


UCLASS()
class THEHAZARDS_API UTheHazardsGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
	// To-Do: Create all SaveGame objects here
	// and spawn them only once when the game starts
public:
	UPROPERTY()
	USaveGameOptions* OptionsSaveObject;

	virtual void Init() override;

	FORCEINLINE class USaveGameOptions* GetOptionsSaveObject() const { return OptionsSaveObject; }
};