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
	Part,
	Blueprint,
	Collectable,
	Miscellaneous,
	Default
};


UENUM(BlueprintType)
enum class EPartTypes : uint8
{
	Barrel,
	Trigger,
	RecoilPad,
	Magazine,
	Grip
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

USTRUCT(BlueprintType)
struct THEHAZARDS_API FPart
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EPartTypes PartType;

	FPart()
	{
		PartType = EPartTypes::Barrel;
	}

	FPart(EPartTypes NewPartType)
	{
		PartType = NewPartType;
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
	EItemSlotTypes EquipSlot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FWeapon WeaponData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FPart PartData;

	FItemBase()
	{
		Name = "Default";
		ItemType = EItemTypes::Default;
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

	// Constructor for parts
	FItemBase(FString NewName, FPart NewPartData)
	{
		Name = NewName;
		ItemType = EItemTypes::Part;
		PartData = NewPartData;
	}
};