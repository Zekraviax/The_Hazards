#include "SpecialAttackActor_Base.h"

#include "Entity_Base.h"


// Sets default values
ASpecialAttackActor_Base::ASpecialAttackActor_Base()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASpecialAttackActor_Base::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ASpecialAttackActor_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}