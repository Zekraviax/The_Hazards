#include "Entity_EnemyNPC.h"

#include "Entity_Player.h"


AEntity_EnemyNPC::AEntity_EnemyNPC(const class FObjectInitializer& ObjectInitializer)
{
	
}


void AEntity_EnemyNPC::BeginPlay()
{
	Super::BeginPlay();
}

void AEntity_EnemyNPC::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	ABaseClass_EnemyController* EnemyController = Cast<ABaseClass_EnemyController>(GetController());
	AEntity_Player* PlayerTarget = nullptr;

	for (TObjectIterator<AEntity_Player> Itr; Itr; ++Itr) {
		//AEntity_Player *FoundPlayer = *Itr;
		PlayerTarget = *Itr;
	}

	if (EnemyController && PlayerTarget != nullptr) {
		EnemyController->SetEnemyBlackboardKey(PlayerTarget);
	}
}