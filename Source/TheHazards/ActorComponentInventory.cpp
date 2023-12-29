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
		ReturnItem = ReturnEquippedPrimaryWeapon();
		break;
	case (ECurrentWeaponEquippedSlot::Secondary):
		ReturnItem = ReturnEquippedSecondaryWeapon();
		break;
	case (ECurrentWeaponEquippedSlot::Tertiary):
		ReturnItem = ReturnEquippedTertiaryWeapon();
		break;
	default:
		ReturnItem = ReturnEquippedPrimaryWeapon();
		break;
	}

	return ReturnItem;
}


FItemBase UActorComponentInventory::ReturnEquippedHeadArmour()
{
	FItemBase HeadArmour;

	for (int i = 0; i < ItemsList.Num(); i++) {
		if (ItemsList[i].SlotInInventory == 1) {
			HeadArmour == ItemsList[i];
			break;
		}
	}

	return HeadArmour;
}

FItemBase UActorComponentInventory::ReturnEquippedTorsoArmour()
{
	FItemBase TorsoArmour;

	for (int i = 0; i < ItemsList.Num(); i++) {
		if (ItemsList[i].SlotInInventory == 2) {
			TorsoArmour == ItemsList[i];
			break;
		}
	}

	return TorsoArmour;
}

FItemBase UActorComponentInventory::ReturnEquippedHandArmour()
{
	FItemBase HandArmour;

	for (int i = 0; i < ItemsList.Num(); i++) {
		if (ItemsList[i].SlotInInventory == 3) {
			HandArmour == ItemsList[i];
			break;
		}
	}

	return HandArmour;
}

FItemBase UActorComponentInventory::ReturnEquippedLegArmour()
{
	FItemBase LegArmour;

	for (int i = 0; i < ItemsList.Num(); i++) {
		if (ItemsList[i].SlotInInventory == 4) {
			LegArmour == ItemsList[i];
			break;
		}
	}

	return LegArmour;
}

FItemBase UActorComponentInventory::ReturnEquippedBootsArmour()
{
	FItemBase BootsArmour;

	for (int i = 0; i < ItemsList.Num(); i++) {
		if (ItemsList[i].SlotInInventory == 5) {
			BootsArmour == ItemsList[i];
			break;
		}
	}

	return BootsArmour;
}


FItemBase UActorComponentInventory::ReturnEquippedPrimaryWeapon()
{
	FItemBase PrimaryWeapon;

	for (int i = 0; i < ItemsList.Num(); i++) {
		if (ItemsList[i].SlotInInventory == 6) {
			PrimaryWeapon == ItemsList[i];
			break;
		}
	}

	return PrimaryWeapon;
}


FItemBase UActorComponentInventory::ReturnEquippedSecondaryWeapon()
{
	FItemBase SecondaryWeapon;

	for (int i = 0; i < ItemsList.Num(); i++) {
		if (ItemsList[i].SlotInInventory == 7) {
			SecondaryWeapon == ItemsList[i];
			break;
		}
	}

	return SecondaryWeapon;
}

FItemBase UActorComponentInventory::ReturnEquippedTertiaryWeapon()
{
	FItemBase TertiaryWeapon;

	for (int i = 0; i < ItemsList.Num(); i++) {
		if (ItemsList[i].SlotInInventory == 8) {
			TertiaryWeapon == ItemsList[i];
			break;
		}
	}

	return TertiaryWeapon;
}

FItemBase UActorComponentInventory::ReturnEquippedQuickUseItem()
{
	FItemBase QuickUseItem;

	for (int i = 0; i < ItemsList.Num(); i++) {
		if (ItemsList[i].SlotInInventory == 9) {
			QuickUseItem == ItemsList[i];
			break;
		}
	}

	return QuickUseItem;
}


float UActorComponentInventory::ReturnTotalDamageMitigation()
{
	return (ReturnEquippedHeadArmour().ArmourData.DamageMitigation +
		ReturnEquippedTorsoArmour().ArmourData.DamageMitigation +
		ReturnEquippedHandArmour().ArmourData.DamageMitigation +
		ReturnEquippedLegArmour().ArmourData.DamageMitigation +
		ReturnEquippedBootsArmour().ArmourData.DamageMitigation);
}