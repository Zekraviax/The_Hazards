#pragma once


#include "CoreMinimal.h"


#include "TheHazardsVariables.generated.h"


// This class is for declaring variables that are used in a wide variety of other classes

UENUM(BlueprintType)
enum class EItemTypes : uint8
{
	EWeapon,
	EArmour,
	EConsumable,
	EAmmo,
	ECustomPart,
	EBlueprint,
	ECollectable,
	EMiscellaneous
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

	FItemBase()
	{
		Name = "Default";
		ItemType = EItemTypes::EWeapon;
	}
};