// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Entity_Base.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BaseClass_EnemyController.h"

#include "Entity_EnemyNPC.generated.h"


UCLASS()
class THE_HAZARDS_API AEntity_EnemyNPC : public AEntity_Base
{
	GENERATED_BODY()

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

private:

public:
// Variables
// --------------------------------------------------

// ------------------------- Artificial Intelligence
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Artificial Intelligence")
	class UBehaviorTree* BehaviorTree;

// Functions
// --------------------------------------------------
	AEntity_EnemyNPC(const class FObjectInitializer& ObjectInitializer);

// ------------------------- Artificial Intelligence

};