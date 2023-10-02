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


void UActorComponentInventory::SetEquippedWeaponSlotEnum(ECurrentWeaponEquippedSlot NewSlotEnum)
{
	CurrentEquippedWeaponSlotEnum = NewSlotEnum;
}


ECurrentWeaponEquippedSlot UActorComponentInventory::ReturnEquippedWeaponSlotEnum()
{
	return CurrentEquippedWeaponSlotEnum;
}


FItemBase UActorComponentInventory::ReturnEquippedWeapon()
{
	FItemBase ReturnItem = FItemBase();

	switch (CurrentEquippedWeaponSlotEnum)
	{
	case (ECurrentWeaponEquippedSlot::Primary):
		ReturnItem = EquippedPrimaryWeapon;
		break;
	case (ECurrentWeaponEquippedSlot::Secondary):
		ReturnItem = EquippedSecondaryWeapon;
		break;
	case (ECurrentWeaponEquippedSlot::Tertiary):
		ReturnItem = EquippedTertiaryWeapon;
		break;
	default:
		ReturnItem = EquippedPrimaryWeapon;
		break;
	}

	return ReturnItem;
}
