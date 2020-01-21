// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"

#include "AIController.h"
#include "BaseClass_EnemyController.h"

#include "BTTask_MoveIntoAttackRange.generated.h"


UCLASS()
class THE_HAZARDS_API UBTTask_MoveIntoAttackRange : public UBTTaskNode
{
	GENERATED_UCLASS_BODY()
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

protected:
	EBTNodeResult::Type MoveToActor(UBehaviorTreeComponent& OwnerComp);
	void ForceStopMovement(ABaseClass_EnemyController* EntityController);

	UPROPERTY(EditAnywhere, Category = Blackboard)
	struct FBlackboardKeySelector EnemyKey;
};