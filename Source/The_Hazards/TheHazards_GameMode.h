// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TheHazards_GameMode.generated.h"

// --------------------------------------------------

// Enums
// --------------------------------------------------

//------------------------- Base Items
UENUM(BlueprintType)
enum class E_Item_Supertypes : uint8
{
	E_Weapon,
	E_Armour,
	E_Consumable,
	E_Ammo,
	E_CustomPart,
	E_Collectable,
	E_Miscellaneous
};

//------------------------- Weapons
UENUM(BlueprintType)
enum class E_Weapon_EquipSlot : uint8
{
	E_Primary,
	E_Secondary,
	E_Tertiary,
};

//------------------------- Characters
UENUM(BlueprintType)
enum class E_Character_Races : uint8
{
	E_Chiropterrian				UMETA(DisplayName = "Chiropterrian"),
	E_Labaredian				UMETA(DisplayName = "Labaredian"),
	E_Detoling					UMETA(DisplayName = "Detoling"),
	E_Frostine					UMETA(DisplayName = "Frostine"),
	E_Celestial					UMETA(DisplayName = "Celestial"),
	E_Human						UMETA(DisplayName = "Human"),
};

UENUM(BlueprintType)
enum class E_Character_Elements : uint8
{
	E_Aer						UMETA(DisplayName = "Aer"),
	E_Aqua						UMETA(DisplayName = "Aqua"),
	E_Ignis						UMETA(DisplayName = "Ignis"),
	E_Terra						UMETA(DisplayName = "Terra"),
	E_Vita						UMETA(DisplayName = "Vita"),
	E_Dynamo					UMETA(DisplayName = "Dynamo"),
};

UENUM(BlueprintType)
enum class E_Character_Factions : uint8
{
	E_XRX						UMETA(DisplayName = "XRX"),
	E_TimesEnd					UMETA(DisplayName = "Time's End"),
	E_GaianGuardians			UMETA(DisplayName = "Gaian Guardians"),
	E_AscendantsReach			UMETA(DisplayName = "Ascendant's Reach"),
	E_GoldenGrasp				UMETA(DisplayName = "Golden Grasp"),
	E_NA						UMETA(DisplayName = "N/A"),
};

//------------------------- Inventory
UENUM(BlueprintType)
enum class E_InventorySlot_EquipType : uint8
{
	E_Armour_Head,
	E_Armour_Body,
	E_Armour_Legs,
	E_Weapon_Primary,
	E_Weapon_Secondary,
	E_Weapon_Tertiary,
};

// Structs
// --------------------------------------------------
USTRUCT()
struct THE_HAZARDS_API FTestStruct
{
	GENERATED_BODY()
};

//------------------------- Entity Base structs
USTRUCT(BlueprintType)
struct THE_HAZARDS_API F_SecondaryStats_Struct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		float Maximum_HealthPoints_Multiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		float HealthPoints_Recovery_Multiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Stats")
		float PhysicalDefence_Multiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Stats")
		float SpecialAttack_Multiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Stats")
		float AttackSpeed_Multiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Stats")
		float MoveSpeed_Multiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Other")
		float IncomingDamage_Multiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Other")
		float OutgoingDamage_Multiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Other")
		float Lifesteal_Percentage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Other")
		float Armour_Value;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Stats")
		float StatusPotency_Multiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Stats")
		float StatusDuration_Multiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Other")
		float ShopDiscount_Multiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Other")
		int Maximum_Companion_Count;

	F_SecondaryStats_Struct()
	{
		Maximum_HealthPoints_Multiplier = 100.f;
		HealthPoints_Recovery_Multiplier = 100.0f;
		PhysicalDefence_Multiplier = 100.f;
		SpecialAttack_Multiplier = 100.f;
		AttackSpeed_Multiplier = 100.f;
		MoveSpeed_Multiplier = 100.0f;
		IncomingDamage_Multiplier = 100.f;
		OutgoingDamage_Multiplier = 100.f;
		Lifesteal_Percentage = 0.f;
		Armour_Value = 0.f;
		StatusPotency_Multiplier = 100.f;
		StatusDuration_Multiplier = 100.f;
		ShopDiscount_Multiplier = 100.f;
		Maximum_Companion_Count = 1;
	}
};

USTRUCT(BlueprintType)
struct THE_HAZARDS_API F_BaseStats_Struct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		float HealthPoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		float HealthPoints_RegenPerSecond;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
		float HealthPoints_RegenStartDelay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aura")
		float AuraPoints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aura")
		float AuraPoints_RegenPerSecond;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aura")
		float AuraPoints_RegenStartDelay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		float Physical_Strength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		float Physical_Defence;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		float Elemental_Strength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		float Elemental_Defence;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		float Attack_Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		float Move_Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		float Evasiveness;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		float Status_Potency;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		float Luck;

	F_BaseStats_Struct()
	{
		HealthPoints = 100.f;
		HealthPoints_RegenPerSecond = 1.f;
		HealthPoints_RegenStartDelay = 5.f;
		AuraPoints = 100.f;
		AuraPoints_RegenPerSecond = 1.f;
		AuraPoints_RegenStartDelay = 5.f;
		Physical_Strength = 10.f;
		Physical_Defence = 10.f;
		Elemental_Strength = 10.f;
		Elemental_Defence = 10.f;
		Attack_Speed = 10.f;
		Move_Speed = 10.f;
		Evasiveness = 10.f;
		Status_Potency = 10.f;
		Luck = 10.f;
	}
};

USTRUCT(BlueprintType)
struct THE_HAZARDS_API F_Entity_CharacterSheet
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base")
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base")
	E_Character_Races Race;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base")
	E_Character_Elements Element;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base")
	E_Character_Factions Faction;

	F_Entity_CharacterSheet()
	{
		Name = "Default";
		Race = E_Character_Races::E_Chiropterrian;
		Element = E_Character_Elements::E_Aer;
		Faction = E_Character_Factions::E_XRX;
	}
};

// ------------------------- Items
USTRUCT(BlueprintType)
struct THE_HAZARDS_API F_Item_WeaponStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enum")
	E_Weapon_EquipSlot EquipSlot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base")
	float DamagePerShot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base")
	float AttackSpeedMultiplier;

	F_Item_WeaponStruct()
	{
		EquipSlot = E_Weapon_EquipSlot::E_Primary;
		DamagePerShot = 1.f;
		AttackSpeedMultiplier = 1.f;
	}
};

USTRUCT(BlueprintType)
struct THE_HAZARDS_API F_Item_BaseStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base")
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base")
	E_Item_Supertypes Supertype;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base")
	int32 IndexInInventoryArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base")
	int32 Amount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Supertypes")
	F_Item_WeaponStruct Weapon;

	F_Item_BaseStruct()
	{
		Name = "Default";
		Supertype = E_Item_Supertypes::E_Miscellaneous;
		IndexInInventoryArray = -1;
		Amount = 0;
	}
};

// --------------------------------------------------

UCLASS()
class THE_HAZARDS_API ATheHazards_GameMode : public AGameModeBase
{
	GENERATED_BODY()

	virtual void StartPlay() override;
};