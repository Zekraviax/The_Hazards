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
enum class EWeaponTypes : uint8
{
	Shotgun
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
	EWeaponTypes WeaponType;

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


USTRUCT(BlueprintType)
struct THEHAZARDS_API FCraftingBlueprintSlotData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Column;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Row;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EPartTypes PartType;

	FCraftingBlueprintSlotData()
	{
		Column = 0;
		Row = 0;
		PartType = EPartTypes::Barrel;
	}

	FCraftingBlueprintSlotData(int InColumn, int InRow, EPartTypes InPartType)
	{
		Column = InColumn;
		Row = InRow;
		PartType = InPartType;
	}
};


USTRUCT(BlueprintType)
struct THEHAZARDS_API FCraftingBlueprint
{
	GENERATED_BODY()

	// Array of slots that this blueprint uses in the crafting window
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FCraftingBlueprintSlotData> CraftingWindowSlots;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EWeaponTypes WeaponType;

	FCraftingBlueprint()
	{
		WeaponType = EWeaponTypes::Shotgun;
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FCraftingBlueprint BlueprintData;

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

	// Constructor for blueprints
	FItemBase(FString NewName, FCraftingBlueprint NewBlueprintData)
	{
		Name = NewName;
		ItemType = EItemTypes::Blueprint;
		BlueprintData = NewBlueprintData;
	}
};