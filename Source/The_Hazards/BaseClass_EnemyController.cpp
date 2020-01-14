// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseClass_EnemyController.h"

#include "Entity_EnemyNPC.h"


ABaseClass_EnemyController::ABaseClass_EnemyController(const class FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	BehaviourComponent = ObjectInitializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviourComponent"));
	BlackboardComponent = ObjectInitializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackboardComponent"));
}


void ABaseClass_EnemyController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	AEntity_EnemyNPC* LocalPawnRef = Cast<AEntity_EnemyNPC>(InPawn);

	if (LocalPawnRef) {
		if (LocalPawnRef->BehaviorTree->BlackboardAsset) {
			BlackboardComponent->InitializeBlackboard(*LocalPawnRef->BehaviorTree->BlackboardAsset);
			if (BehaviourComponent) {
				BehaviourComponent->StartTree(*LocalPawnRef->BehaviorTree);
			}
		}
	}
}


void ABaseClass_EnemyController::SetEnemyBlackboardKey(APawn* NewTarget)
{
	if (BlackboardComponent) {
		if (BlackboardComponent->GetValueAsObject("Enemy") != NewTarget) {
			BlackboardComponent->SetValueAsObject("Enemy", NewTarget);
		}
	}
}