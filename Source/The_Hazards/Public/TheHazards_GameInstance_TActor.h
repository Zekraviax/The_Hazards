#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TheHazards_GameInstance_TActor.generated.h"

// Forward Declarations
class UBaseClass_Widget_LoadScreen;
class UTheHazards_GameInstance;


UCLASS()
class THE_HAZARDS_API ATheHazards_GameInstance_TActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATheHazards_GameInstance_TActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

// Base Variables
// --------------------------------------------------
	UPROPERTY()
	FTimerHandle TimerHandle;

// ------------------------- References
	UPROPERTY()
	UBaseClass_Widget_LoadScreen* LoadingScreenReference;

	UPROPERTY()
	UTheHazards_GameInstance* GameInstanceReference;

// Functions
// --------------------------------------------------

// ------------------------- Save/Load
	UFUNCTION()
	void ClearLoadingScreenTimer();

	UFUNCTION()
	void ClearLoadingScreenFunction();
};
