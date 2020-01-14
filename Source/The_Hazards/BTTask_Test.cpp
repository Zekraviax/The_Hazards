// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Test.h"


EBTNodeResult::Type UBTTask_Test::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Successfully ran BTTask_Test"));

	EBTNodeResult::Type NodeResult = EBTNodeResult::Succeeded;
	return NodeResult;
}
