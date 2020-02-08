// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Test.h"


UBTTask_Test::UBTTask_Test(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Passive: Test";
}


EBTNodeResult::Type UBTTask_Test::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Attempting to run BTTask_Test"));

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Successfully ran BTTask_Test"));
	EBTNodeResult::Type NodeResult = EBTNodeResult::Succeeded;
	return NodeResult;
}
