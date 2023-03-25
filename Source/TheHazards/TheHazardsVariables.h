#pragma once


#include "CoreMinimal.h"


#include "TheHazardsVariables.generated.h"


// This class is for declaring variables that are used in a wide variety of other classes


UENUM(BlueprintType)
enum class EItemTypes : uint8
{
	Weapon,
	Armour,
	Consumable,
	Ammo,
	CustomPart,
	Blueprint,
	Collectable,
	Miscellaneous
};


UENUM(BlueprintType)
enum class EItemSlotTypes : uint8
{
	Default,
	Head,
	Body,
	Legs,
	Boots,
	PrimaryWeapon,
	SecondaryWeapon,
};


// Weapons
USTRUCT(BlueprintType)
struct THEHAZARDS_API FWeapon
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DamagePerShot;

	FWeapon()
	{
		DamagePerShot = 1.f;
	}

	FWeapon(float NewDamagePerShot) 
	{
		DamagePerShot = NewDamagePerShot;
	}
};


// Items
USTRUCT(BlueprintType)
struct THEHAZARDS_API FItemBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EItemTypes ItemType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FWeapon WeaponData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EItemSlotTypes EquipSlot;

	FItemBase()
	{
		Name = "Default";
		ItemType = EItemTypes::Weapon;
		EquipSlot = EItemSlotTypes::PrimaryWeapon;
	}

	// Constructor for weapons
	FItemBase(FString NewName, FWeapon NewWeaponData)
	{
		Name = NewName;
		ItemType = EItemTypes::Weapon;
		WeaponData = NewWeaponData;
		EquipSlot = EItemSlotTypes::PrimaryWeapon;
	}
};