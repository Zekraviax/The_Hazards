#pragma once


#include "CoreMinimal.h"

#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "InterfaceInteractions.h"

#include "ActorInteractable.generated.h"


class AEntityBaseCharacter;


UCLASS()
class THEHAZARDS_API AActorInteractable : public AActor, public IInterfaceInteractions
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AActorInteractable();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// To-Do: Explain this
	// Function Interface ?
	virtual bool OnInteract_Implementation() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Currently overlapped entity
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AEntityBaseCharacter* OverlappingEntity;

	// Entities must be within this box in order to interact with this object
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* InteractBounds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* Root;
};
