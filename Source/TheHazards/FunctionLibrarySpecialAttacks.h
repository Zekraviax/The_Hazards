#pragma once

#include "CoreMinimal.h"

#include "Kismet/BlueprintFunctionLibrary.h"
#include "TimerManager.h"

#include "FunctionLibrarySpecialAttacks.generated.h"


// Forward Declarations
class AEntityBaseCharacter;


UCLASS()
class THEHAZARDS_API UFunctionLibrarySpecialAttacks : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
// -------- Sickle
	UFUNCTION()
	static void SickleSpecialAttackBegin(AEntityBaseCharacter* Attacker);
};