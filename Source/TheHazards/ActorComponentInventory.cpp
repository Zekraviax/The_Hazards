#include "ActorComponentInventory.h"


// Sets default values for this component's properties
UActorComponentInventory::UActorComponentInventory()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UActorComponentInventory::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UActorComponentInventory::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


void UActorComponentInventory::ReturnEquippedWeaponsData(float& DamagePerShot)
{
	DamagePerShot = EquippedPrimaryWeapon.WeaponData.DamagePerShot;
}