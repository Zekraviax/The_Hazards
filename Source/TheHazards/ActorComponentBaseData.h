#pragma once


#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ActorComponentBaseData.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THEHAZARDS_API UActorComponentBaseData : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UActorComponentBaseData();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Core)
	FString Name = "Default";
};
