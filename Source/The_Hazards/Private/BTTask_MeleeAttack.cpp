

#include "BTTask_MeleeAttack.h"


UBTTask_MeleeAttack::UBTTask_MeleeAttack(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Aggressive: Melee Attack";
}

EBTNodeResult::Type UBTTask_MeleeAttack::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	// Get Variables
	AEntity_Base* Pawn = Cast<AEntity_Base>(OwnerComp.GetAIOwner()->GetPawn());

	// Begin
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Attempting to run BTTask_MeleeAttack"));
	EBTNodeResult::Type NodeResult = EBTNodeResult::InProgress;

	Pawn->AttackStart();

	// Finish
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Successfully ran BTTask_MeleeAttack"));
	NodeResult = EBTNodeResult::Succeeded;
	return NodeResult;
}