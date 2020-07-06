#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpecialAttackActor_Base.generated.h"


UCLASS()
class THE_HAZARDS_API ASpecialAttackActor_Base : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpecialAttackActor_Base();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};