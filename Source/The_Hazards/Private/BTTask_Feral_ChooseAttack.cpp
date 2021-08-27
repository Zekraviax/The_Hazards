#include "BTTask_Feral_ChooseAttack.h"


UBTTask_Feral_ChooseAttack::UBTTask_Feral_ChooseAttack(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Aggressive - Feral: Choose Attack";
}


EBTNodeResult::Type UBTTask_Feral_ChooseAttack::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	EBTNodeResult::Type NodeResult = EBTNodeResult::InProgress;
	TMap<FString, int> LocalAttacksMap = Cast<ABaseClass_EnemyController>(OwnerComp.GetAIOwner())->AttacksAndRangesMap;
	TArray<FString> AttackNamesArray;
	TArray<int> AttackRangesArray;
	FString ChosenAttackName;
	int ChosenAttackRange;

	// Begin
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, TEXT("Attempting to run BTTask_Feral_ChooseAttack"));

	// Choose an attack at random
	for (TMap<FString, int>::TIterator itr = LocalAttacksMap.CreateIterator(); itr; ++itr)
	{
		AttackNamesArray.Add(itr->Key);
		AttackRangesArray.Add(itr->Value);
	}

	if (AttackNamesArray.Num() > 0) {
		ChosenAttackName = AttackNamesArray[FMath::RandRange(0, AttackNamesArray.Num() - 1)];
		ChosenAttackRange = AttackRangesArray[FMath::RandRange(0, AttackRangesArray.Num() - 1)];

		// Set blackboard values
		OwnerComp.GetBlackboardComponent()->SetValueAsString("CurrentAttackName", ChosenAttackName);
		OwnerComp.GetBlackboardComponent()->SetValueAsInt("CurrentAttackRange", ChosenAttackRange);
	}


	// End
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Successfully ran BTTask_Feral_ChooseAttack"));
	NodeResult = EBTNodeResult::Succeeded;
	return NodeResult;
}