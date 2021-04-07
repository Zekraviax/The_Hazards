// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "BaseClass_EnemyController.generated.h"


UCLASS()
class THE_HAZARDS_API ABaseClass_EnemyController : public AAIController
{
	GENERATED_BODY()

	ABaseClass_EnemyController(const class FObjectInitializer& ObjectInitializer);

	virtual void OnPossess(class APawn* InPawn) override;

	UBlackboardComponent* BlackboardComponent;

	UBehaviorTreeComponent* BehaviourComponent;

protected:

public:
// Variables
// --------------------------------------------------

// ------------------------- Artificial Intelligence
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Artificial Intelligence")
	TMap<FString, int> AttacksAndRangesMap;

// Functions
// --------------------------------------------------
	
// ------------------------- Artificial Intelligence
	UFUNCTION()
	void SetEnemyBlackboardKey(APawn* NewTarget);
};
