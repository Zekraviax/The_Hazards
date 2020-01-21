// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"

#include "Entity_Base.h"
#include "AIController.h"

#include "BTTask_MeleeAttack.generated.h"


UCLASS()
class THE_HAZARDS_API UBTTask_MeleeAttack : public UBTTaskNode
{
	GENERATED_UCLASS_BODY()
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
