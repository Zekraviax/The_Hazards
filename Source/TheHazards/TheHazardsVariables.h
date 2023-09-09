#pragma once


#include "CoreMinimal.h"


#include "TheHazardsVariables.generated.h"


// This class is for declaring variables that are used in a wide variety of other classes


UENUM(BlueprintType)
enum class EItemTypes : uint8
{
	None,
	Weapon,
	Armour,
	Consumable,
	Ammo,
	Part,
	Blueprint,
	Collectable,
	Miscellaneous
};


UENUM(BlueprintType)
enum class EWeaponTypes : uint8
{
	None,
	Shotgun
};


UENUM(BlueprintType)
enum class EPartTypes : uint8
{
	None,
	Barrel,
	Trigger,
	RecoilPad,
	Magazine,
	Grip
};


UENUM(BlueprintType)
enum class EItemSlotTypes : uint8
{
	None,
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
		WeaponType = EWeaponTypes::None;
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

	// Parts shouldn't have variables that are exact copies of other item types' variables
	// because we can just use those variables instead
	// For example, we don't need this DamagePerShot variable because the WeaponType struct already has it
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//float DamagePerShot;

	FPart()
	{
		PartType = EPartTypes::None;
	}

	FPart(EPartTypes NewPartType, float NewDPS)
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
		PartType = EPartTypes::None;
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
	EItemTypes CraftedItemType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EWeaponTypes WeaponType;

	FCraftingBlueprint()
	{
		CraftedItemType = EItemTypes::Weapon;
		WeaponType = EWeaponTypes::None;
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

	// Default constructor
	FItemBase()
	{
		Name = "Default";
		ItemType = EItemTypes::None;
		EquipSlot = EItemSlotTypes::PrimaryWeapon;
		WeaponData = FWeapon();
		PartData = FPart();
		BlueprintData = FCraftingBlueprint();
	}

	// Comparator
	FORCEINLINE bool operator== (const FItemBase& OtherItem) 
	{
		if (Name == OtherItem.Name &&
			ItemType == OtherItem.ItemType &&
			EquipSlot == OtherItem.EquipSlot) {
			return true;
		}

		return false;
	}


	// Constructor for weapons
	FItemBase(FString NewName, FWeapon CraftedItemData)
	{
		Name = NewName;
		ItemType = EItemTypes::Weapon;
		WeaponData = CraftedItemData;
		EquipSlot = EItemSlotTypes::PrimaryWeapon;
		PartData = FPart();
		BlueprintData = FCraftingBlueprint();
	}

	// Constructor for parts
	FItemBase(FString NewName, FPart NewPartData)
	{
		Name = NewName;
		ItemType = EItemTypes::Part;
		WeaponData = FWeapon();
		PartData = NewPartData;
		BlueprintData = FCraftingBlueprint();
	}

	// Constructor for blueprints
	FItemBase(FString NewName, FCraftingBlueprint NewBlueprintData)
	{
		Name = NewName;
		ItemType = EItemTypes::Blueprint;
		BlueprintData = NewBlueprintData;
		WeaponData = FWeapon();
		PartData = FPart();
	}
};