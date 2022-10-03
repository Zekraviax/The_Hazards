#pragma once


#include "CoreMinimal.h"

#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "InterfaceInteractions.h"

#include "ActorInteractable.generated.h"


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


	virtual bool OnInteract_Implementation() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Entities must be within this box in order to interact with this object
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* InteractBounds;
};
