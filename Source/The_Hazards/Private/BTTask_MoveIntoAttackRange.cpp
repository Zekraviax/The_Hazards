#include "BTTask_MoveIntoAttackRange.h"

#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/BlackboardComponent.h"


UBTTask_MoveIntoAttackRange::UBTTask_MoveIntoAttackRange(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Special: Move Into Attack Range";
	bNotifyTick = true;
}


EBTNodeResult::Type UBTTask_MoveIntoAttackRange::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8 * NodeMemory)
{
	// Begin
//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, TEXT("Attempting to run BTTask_MoveIntoAttackRange"));
	EBTNodeResult::Type NodeResult = EBTNodeResult::InProgress;

	// Finish
	NodeResult = MoveToActor(OwnerComp);
	return NodeResult;
}


void UBTTask_MoveIntoAttackRange::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	ABaseClass_EnemyController* EntityController = Cast<ABaseClass_EnemyController>(OwnerComp.GetAIOwner());
	AActor* TargetActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("Enemy"));
	int AttackRange = OwnerComp.GetBlackboardComponent()->GetValueAsInt("CurrentAttackRange");

	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Magenta, "Distance: " + FString::SanitizeFloat(EntityController->GetPawn()->GetDistanceTo(TargetActor)));

	if (EntityController->GetPawn()->GetDistanceTo(TargetActor) <= AttackRange) {
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, "Stop Movement");

		if (EntityController) {
			ForceStopMovement(EntityController);
		}

		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}


EBTNodeResult::Type UBTTask_MoveIntoAttackRange::MoveToActor(UBehaviorTreeComponent& OwnerComp)
{
	AAIController* EntityController = OwnerComp.GetAIOwner();
	AActor* TargetActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject("Enemy"));
	EBTNodeResult::Type NodeResult = EBTNodeResult::InProgress;
	int AttackRange = OwnerComp.GetBlackboardComponent()->GetValueAsInt("CurrentAttackRange");
	float EntityVectorLength, TargetVectorLength = 0;


	if (EntityController && TargetActor) {
		EntityVectorLength = (EntityController->GetPawn()->GetActorLocation().Size());
		TargetVectorLength = TargetActor->GetActorLocation().Size();

		//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Magenta, "Distance: " + FString::SanitizeFloat(EntityController->GetPawn()->GetDistanceTo(TargetActor)));

		if (EntityController->GetPawn()->GetDistanceTo(TargetActor) > AttackRange) {
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Move Into Attack Range"));

			EntityController->MoveToActor(TargetActor, 50.f, true, true, true);
			NodeResult = EBTNodeResult::InProgress;
		}
	}

	return NodeResult;
}

void UBTTask_MoveIntoAttackRange::ForceStopMovement(ABaseClass_EnemyController* EntityController)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Orange, "Force Stop Movement");
	EntityController->StopMovement();
}