#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "Engine/DataTable.h"

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
	E_Blueprint,
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

//------------------------- Armour
UENUM(BlueprintType)
enum class E_Armour_EquipSlot : uint8
{
	E_Head,
	E_Body,
	E_Legs,
};

//------------------------- Custom Parts
UENUM(BlueprintType)
enum class E_CustomPart_Types : uint8
{
	E_Blade,
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

//------------------------- Skills
UENUM(BlueprintType)
enum class E_Skill_ActivationCondition : uint8
{
	E_Base,
	E_Passive,
	E_OnDamageDealt,
	E_OnDamageTaken,
};

//------------------------- Special Attacks
UENUM(BlueprintType)
enum class E_Weapon_AttackStyles : uint8
{
	E_None,
	E_Melee_Swing,
	E_Melee_Thrust,
	E_Ranged_SingleShot,
	E_Ranged_BurstFire,
	E_Ranged_FullAuto
};

//------------------------- Special Attacks
UENUM(BlueprintType)
enum class E_Weapon_SpecialAttacks : uint8
{
	E_None,
	E_Assassinate,
};

//------------------------- NPC
UENUM(BlueprintType)
enum class E_Conversation_NextActionInConversation : uint8
{
	E_OpenNextDialogueLine,
	E_OpenShop,
	E_OpenDialogueBranch,
	E_CloseDialogue,
};

//------------------------- Artificial Intelligence
UENUM(BlueprintType)
enum class E_Behaviours_Archetypes : uint8
{
	E_Defensive,
};

UENUM(BlueprintType)
enum class E_Behaviours_Passive : uint8
{
	E_Sleep,
};

UENUM(BlueprintType)
enum class E_Behaviours_Agressive : uint8
{
	E_Feral,
};

// Structs
// --------------------------------------------------
USTRUCT()
struct THE_HAZARDS_API FTestStruct
{
	GENERATED_BODY()
};

//------------------------- Entity Base
USTRUCT(BlueprintType)
struct THE_HAZARDS_API F_SecondaryStats_Struct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health and Aura")
	float Maximum_HealthPoints_Multiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health and Aura")
	float HealthPoints_Recovery_Multiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health and Aura")
	float HealthPoints_Delay_Multiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health and Aura")
	float Maximum_AuraPoints_Multiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health and Aura")
	float AuraPoints_Recovery_Multiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health and Aura")
	float AuraPoints_Delay_Multiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Stats")
	float PhysicalStrength_Multiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Stats")
	float PhysicalDefence_Multiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Stats")
	float ElementalStrength_Multiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Stats")
	float ElementalDefence_Multiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Stats")
	float AttackSpeed_Multiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Stats")
	float MoveSpeed_Multiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Stats")
	float Evasiveness_Multiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Stats")
	float StatusPotency_Multiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base Stats")
	float Luck_Multiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Other")
	float IncomingDamage_Multiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Other")
	float OutgoingDamage_Multiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Other")
	float Lifesteal_Percentage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Other")
	float Armour_Value;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Other")
	float StatusDuration_Multiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Other")
	float ShopDiscount_Multiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Other")
	int Maximum_Companion_Count;

	F_SecondaryStats_Struct()
	{
		Maximum_HealthPoints_Multiplier = 1.f;
		HealthPoints_Recovery_Multiplier = 1.f;
		HealthPoints_Delay_Multiplier = 1.f;
		Maximum_AuraPoints_Multiplier = 1.f;
		AuraPoints_Recovery_Multiplier = 1.f;
		AuraPoints_Delay_Multiplier = 1.f;
		PhysicalStrength_Multiplier = 1.f;
		PhysicalDefence_Multiplier = 1.f;
		ElementalStrength_Multiplier = 1.f;
		ElementalDefence_Multiplier = 1.f;
		AttackSpeed_Multiplier = 1.f;
		MoveSpeed_Multiplier = 1.f;
		Evasiveness_Multiplier = 1.f;
		StatusPotency_Multiplier = 1.f;
		Luck_Multiplier = 1.f;
		IncomingDamage_Multiplier = 1.f;
		OutgoingDamage_Multiplier = 1.f;
		Lifesteal_Percentage = 1.f;
		Armour_Value = 1.f;
		StatusDuration_Multiplier = 1.f;
		ShopDiscount_Multiplier = 1.f;
		Maximum_Companion_Count = 1;
	}

	F_SecondaryStats_Struct(const float& InMaximumHealthPointsMultiplier, const float& InHealthPointsRecoveryMultiplier, const float& InHealthPointsDelayMultiplier, 
		const float& InMaximumAuraPointsMultiplier, const float& InAuraPointsRecoveryMultiplier, const float& InAuraPointsDelayMultiplier,
		const float& InPhysicalStrengthMultiplier, const float& InPhysicalDefenceMultiplier, const float& InElementalStrengthMultiplier, const float& InElementalDefenceMultiplier,
		const float& InAttackSpeedMultiplier, const float& InMoveSpeedMultiplier, const float& InEvasivenessMultiplier, const float& InStatusPotencyMultiplier,
		const float& InLuckMultiplier, const float& InIncomingDamageMultiplier, const float& InOutgoingDamageMultiplier, const float& InLifestealPercentage,
		const float& InArmourValue, const float& InStatusDurationMultiplier, const float& InShopDiscountMultiplier, const int& InMaximumCompanionCount)
	{
		Maximum_HealthPoints_Multiplier = InMaximumHealthPointsMultiplier;
		HealthPoints_Recovery_Multiplier = InHealthPointsRecoveryMultiplier;
		HealthPoints_Delay_Multiplier = InHealthPointsDelayMultiplier;
		Maximum_AuraPoints_Multiplier = InMaximumAuraPointsMultiplier;
		AuraPoints_Recovery_Multiplier = InAuraPointsRecoveryMultiplier;
		AuraPoints_Delay_Multiplier = InAuraPointsDelayMultiplier;
		PhysicalStrength_Multiplier = InPhysicalStrengthMultiplier;
		PhysicalDefence_Multiplier = InPhysicalDefenceMultiplier;
		ElementalStrength_Multiplier = InElementalStrengthMultiplier;
		ElementalDefence_Multiplier = InElementalDefenceMultiplier;
		AttackSpeed_Multiplier = InAttackSpeedMultiplier;
		MoveSpeed_Multiplier = InMoveSpeedMultiplier;
		Evasiveness_Multiplier = InEvasivenessMultiplier;
		StatusPotency_Multiplier = InStatusPotencyMultiplier;
		Luck_Multiplier = InLuckMultiplier;
		IncomingDamage_Multiplier = InIncomingDamageMultiplier;
		OutgoingDamage_Multiplier = InOutgoingDamageMultiplier;
		Lifesteal_Percentage = InLifestealPercentage;
		Armour_Value = InArmourValue;
		StatusDuration_Multiplier = InStatusDurationMultiplier;
		ShopDiscount_Multiplier = InShopDiscountMultiplier;
		Maximum_Companion_Count = InMaximumCompanionCount;
	}

	FORCEINLINE bool operator==(const F_SecondaryStats_Struct& OtherSecondaryStatStruct) const
	{
		if (Maximum_HealthPoints_Multiplier == OtherSecondaryStatStruct.Maximum_HealthPoints_Multiplier &&
			HealthPoints_Recovery_Multiplier == OtherSecondaryStatStruct.HealthPoints_Recovery_Multiplier &&
			HealthPoints_Delay_Multiplier == OtherSecondaryStatStruct.HealthPoints_Delay_Multiplier &&
			Maximum_AuraPoints_Multiplier == OtherSecondaryStatStruct.Maximum_AuraPoints_Multiplier &&
			AuraPoints_Recovery_Multiplier == OtherSecondaryStatStruct.AuraPoints_Recovery_Multiplier &&
			AuraPoints_Delay_Multiplier == OtherSecondaryStatStruct.AuraPoints_Delay_Multiplier &&
			PhysicalStrength_Multiplier == OtherSecondaryStatStruct.PhysicalStrength_Multiplier &&
			PhysicalDefence_Multiplier == OtherSecondaryStatStruct.PhysicalDefence_Multiplier &&
			ElementalStrength_Multiplier == OtherSecondaryStatStruct.ElementalStrength_Multiplier &&
			ElementalDefence_Multiplier == OtherSecondaryStatStruct.ElementalDefence_Multiplier &&
			AttackSpeed_Multiplier == OtherSecondaryStatStruct.AttackSpeed_Multiplier &&
			MoveSpeed_Multiplier == OtherSecondaryStatStruct.MoveSpeed_Multiplier &&
			Evasiveness_Multiplier == OtherSecondaryStatStruct.Evasiveness_Multiplier &&
			StatusPotency_Multiplier == OtherSecondaryStatStruct.StatusPotency_Multiplier &&
			Luck_Multiplier == OtherSecondaryStatStruct.Luck_Multiplier &&
			IncomingDamage_Multiplier == OtherSecondaryStatStruct.IncomingDamage_Multiplier &&
			OutgoingDamage_Multiplier == OtherSecondaryStatStruct.OutgoingDamage_Multiplier &&
			Lifesteal_Percentage == OtherSecondaryStatStruct.Lifesteal_Percentage &&
			Armour_Value == OtherSecondaryStatStruct.Armour_Value &&
			StatusDuration_Multiplier == OtherSecondaryStatStruct.StatusDuration_Multiplier &&
			ShopDiscount_Multiplier == OtherSecondaryStatStruct.ShopDiscount_Multiplier &&
			Maximum_Companion_Count == OtherSecondaryStatStruct.Maximum_Companion_Count) {
			return true;
		}
		else {
			return false;
		}
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	F_SecondaryStats_Struct SecondaryStats;

	F_BaseStats_Struct()
	{
		HealthPoints = 1.f;
		HealthPoints_RegenPerSecond = 1.f;
		HealthPoints_RegenStartDelay = 1.f;
		AuraPoints = 1.f;
		AuraPoints_RegenPerSecond = 1.f;
		AuraPoints_RegenStartDelay = 1.f;
		Physical_Strength = 1.f;
		Physical_Defence = 1.f;
		Elemental_Strength = 1.f;
		Elemental_Defence = 1.f;
		Attack_Speed = 1.f;
		Move_Speed = 1.f;
		Evasiveness = 1.f;
		Status_Potency = 1.f;
		Luck = 1.f;
	}

	F_BaseStats_Struct(const float& InHealthPoints, const float& InHealthPointsRegenPerSecond, const float& InHealthPointsRegenStartDelay,
		const float& InAuraPoints, const float& InAuraPointsRegenPerSecond, const float& InAuraPointsRegenStartDelay,
		const float& InPhysicalStrength, const float& InPhysicalDefence, const float& InElementalStrength, const float& InElementalDefence,
		const float& InAttackSpeed, const float& InMoveSpeed, const float& InEvasiveness, const float& InStatusPotency, const float& InLuck)
	{
		HealthPoints = InHealthPoints;
		HealthPoints_RegenPerSecond = InHealthPointsRegenPerSecond;
		HealthPoints_RegenStartDelay = InHealthPointsRegenStartDelay;
		AuraPoints = InAuraPoints;
		AuraPoints_RegenPerSecond = InAuraPointsRegenPerSecond;
		AuraPoints_RegenStartDelay = InAuraPointsRegenStartDelay;
		Physical_Strength = InPhysicalStrength;
		Physical_Defence = InPhysicalDefence;
		Elemental_Strength = InElementalStrength;
		Elemental_Defence = InElementalDefence;
		Attack_Speed = InAttackSpeed;
		Move_Speed = InMoveSpeed;
		Evasiveness = InEvasiveness;
		Status_Potency = InStatusPotency;
		Luck = InLuck;
	}

	FORCEINLINE bool operator==(const F_BaseStats_Struct& OtherBaseStatStruct) const
	{
		if (HealthPoints == OtherBaseStatStruct.HealthPoints && 
			HealthPoints_RegenPerSecond == OtherBaseStatStruct.HealthPoints_RegenPerSecond && 
			HealthPoints_RegenStartDelay == OtherBaseStatStruct.HealthPoints_RegenStartDelay &&
			AuraPoints == OtherBaseStatStruct.AuraPoints &&
			AuraPoints_RegenPerSecond == OtherBaseStatStruct.AuraPoints_RegenPerSecond &&
			AuraPoints_RegenStartDelay == OtherBaseStatStruct.AuraPoints_RegenStartDelay &&
			Physical_Strength == OtherBaseStatStruct.Physical_Strength &&
			Physical_Defence == OtherBaseStatStruct.Physical_Defence &&
			Elemental_Strength == OtherBaseStatStruct.Elemental_Strength &&
			Elemental_Defence == OtherBaseStatStruct.Elemental_Defence &&
			Attack_Speed == OtherBaseStatStruct.Attack_Speed &&
			Move_Speed == OtherBaseStatStruct.Move_Speed &&
			Evasiveness == OtherBaseStatStruct.Evasiveness &&
			Status_Potency == OtherBaseStatStruct.Status_Potency &&
			Luck == OtherBaseStatStruct.Luck &&
			SecondaryStats == OtherBaseStatStruct.SecondaryStats) {
			return true;
		}
		else {
			return false;
		}
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enum")
	E_Weapon_AttackStyles AttackStyle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base")
	float DamagePerShot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base")
	float AttackSpeedMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	F_BaseStats_Struct StatModifiers;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Special")
	E_Weapon_SpecialAttacks SpecialAttack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Special")
	int SpecialAttackCost;

	// Special Attack Modifiers

	F_Item_WeaponStruct()
	{
		EquipSlot = E_Weapon_EquipSlot::E_Primary;
		AttackStyle = E_Weapon_AttackStyles::E_None;
		DamagePerShot = 1.f;
		AttackSpeedMultiplier = 1.f;
		SpecialAttack = E_Weapon_SpecialAttacks::E_None;
		SpecialAttackCost = 20;
	}

	FORCEINLINE bool operator==(const F_Item_WeaponStruct& OtherWeapon) const
	{
		if (EquipSlot == OtherWeapon.EquipSlot &&
			AttackStyle == OtherWeapon.AttackStyle &&
			DamagePerShot == OtherWeapon.DamagePerShot &&
			AttackSpeedMultiplier == OtherWeapon.AttackSpeedMultiplier &&
			StatModifiers == OtherWeapon.StatModifiers &&
			SpecialAttack == OtherWeapon.SpecialAttack &&
			SpecialAttackCost == OtherWeapon.SpecialAttackCost) {
			return true;
		}
		else {
			return false;
		}
	}
};

USTRUCT(BlueprintType)
struct THE_HAZARDS_API F_Item_ArmourStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enum")
	E_Armour_EquipSlot EquipSlot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base")
	int32 ArmourValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	F_BaseStats_Struct StatModifiers;

	F_Item_ArmourStruct()
	{
		EquipSlot = E_Armour_EquipSlot::E_Head;
		ArmourValue = 0;
	}

	FORCEINLINE bool operator==(const F_Item_ArmourStruct& OtherArmour) const
	{
		if (EquipSlot == OtherArmour.EquipSlot &&
			ArmourValue == OtherArmour.ArmourValue &&
			StatModifiers == OtherArmour.StatModifiers) {
			return true;
		} else {
			return false;
		}
	}
};

USTRUCT(BlueprintType)
struct THE_HAZARDS_API F_Item_BlueprintStruct
{
	GENERATED_BODY()

	// Item type?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base")
	E_Item_Supertypes ItemType;

	F_Item_BlueprintStruct()
	{
		ItemType = E_Item_Supertypes::E_Weapon;
	}

	FORCEINLINE bool operator==(const F_Item_BlueprintStruct& OtherBlueprint) const
	{
		if (ItemType == OtherBlueprint.ItemType) {
			return true;
		} else {
			return false;
		}
	}
};

USTRUCT(BlueprintType)
struct THE_HAZARDS_API F_Item_CustomPartStruct
{
	GENERATED_BODY()

	// Part type?
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base")
	E_CustomPart_Types Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	F_BaseStats_Struct StatModifiers;

	F_Item_CustomPartStruct()
	{
		Type = E_CustomPart_Types::E_Blade;
	}

	FORCEINLINE bool operator==(const F_Item_CustomPartStruct& OtherCustomPart) const
	{
		if (Type == OtherCustomPart.Type &&
			StatModifiers == OtherCustomPart.StatModifiers) {
			return true;
		}
		else {
			return false;
		}
	}

};

USTRUCT(BlueprintType)
struct THE_HAZARDS_API F_Item_BaseStruct : public FTableRowBase
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base")
	int32 Value;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base")
	UTexture2D* InventoryImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Supertypes")
	F_Item_WeaponStruct Weapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Supertypes")
	F_Item_ArmourStruct Armour;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Supertypes")
	F_Item_BlueprintStruct Blueprint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Supertypes")
	F_Item_CustomPartStruct CustomPart;

	F_Item_BaseStruct()
	{
		Name = "Default";
		Supertype = E_Item_Supertypes::E_Miscellaneous;
		IndexInInventoryArray = -1;
		Amount = 0;
		Value = 1;
		InventoryImage = NULL;
	}

	FORCEINLINE bool operator==(const F_Item_BaseStruct& OtherItem) const
	{
		if (Name == OtherItem.Name &&
			Supertype == OtherItem.Supertype &&
			InventoryImage == OtherItem.InventoryImage &&
			Weapon == OtherItem.Weapon &&
			Armour == OtherItem.Armour &&
			Blueprint == OtherItem.Blueprint &&
			CustomPart == OtherItem.CustomPart) {
			return true;
		} else {
			return false;
		}
	}
};

// ------------------------- Skills
USTRUCT(BlueprintType)
struct THE_HAZARDS_API F_Skill_Base : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base")
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base")
	E_Character_Elements Element;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base")
	FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int32 CurrentLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int32 MaximumLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display")
	UTexture2D* SkillImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Function")
	E_Skill_ActivationCondition ActivationCondition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Function")
	int32 SkillIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Technical")
	int32 SlotNumber;

	F_Skill_Base()
	{
		Name = "Default";
		Element = E_Character_Elements::E_Aer;
		Description = "Default.";
		CurrentLevel = 0;
		MaximumLevel = 1;
		SkillImage = NULL;
		ActivationCondition = E_Skill_ActivationCondition::E_Passive;
		SkillIndex = 1;
		SlotNumber = 0;
	}
};

// ------------------------- Status Effects
USTRUCT(BlueprintType)
struct THE_HAZARDS_API F_StatusEffect_Base : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base")
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Base")
	E_Character_Elements Element;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display")
	UTexture2D* StatusEffectImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time")
	int CurrentStackCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Time")
	float CurrentTime;


	F_StatusEffect_Base()
	{
		Name = "Default";
		Element = E_Character_Elements::E_Aer;
		StatusEffectImage = NULL;
		CurrentStackCount = 1;
		CurrentTime = 0.f;
	}
};

// ------------------------- NPC
USTRUCT(BlueprintType)
struct THE_HAZARDS_API F_Dialogue_Branch
{
	GENERATED_BODY()

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	//FString SpeakerName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	FString DialogueLine;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	//UTexture2D* SpeakerImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Technical")
	int32 NextLineIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Technical")
	E_Conversation_NextActionInConversation NextAction;

	F_Dialogue_Branch()
	{
		//SpeakerName = "Default";
		DialogueLine = "Default.";
		//SpeakerImage = NULL;
		NextLineIndex = -1;
		NextAction = E_Conversation_NextActionInConversation::E_OpenNextDialogueLine;
	}
};

USTRUCT(BlueprintType)
struct THE_HAZARDS_API F_Dialogue_Entry
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dialogue")
	FString DialogueLine;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Technical")
	int32 NextLineIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speaker")
	FString SpeakerName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speaker")
	UTexture2D* SpeakerImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speaker")
	E_Conversation_NextActionInConversation NextActionInConversation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Technical")
	TArray<F_Dialogue_Branch> DialogueBranchOptions;

	F_Dialogue_Entry()
	{
		DialogueLine = "Default.";
		NextLineIndex = -1;
		SpeakerName = "Default";
		SpeakerImage = NULL;
		NextActionInConversation = E_Conversation_NextActionInConversation::E_CloseDialogue;
	}
};

USTRUCT(BlueprintType)
struct THE_HAZARDS_API F_Dialogue_Shop
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Technical")
	int32 IndexInConversation;

	F_Dialogue_Shop()
	{
		IndexInConversation = -1;
	}
};

//USTRUCT(BlueprintType)
//struct THE_HAZARDS_API F_Dialogue_Branch
//{
//	GENERATED_BODY()
//
//	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Technical")
//	int32 IndexInConversation;
//
//	F_Dialogue_Branch()
//	{
//		IndexInConversation = -1;
//	}
//};

// ------------------------- Artificial Intelligence
USTRUCT(BlueprintType)
struct THE_HAZARDS_API F_AI_Behaviours
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	E_Behaviours_Archetypes ArchetypeBehaviour;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	E_Behaviours_Passive PassiveBehaviour;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	E_Behaviours_Agressive AgressiveBehaviour;

	F_AI_Behaviours()
	{
		ArchetypeBehaviour = E_Behaviours_Archetypes::E_Defensive;
		PassiveBehaviour = E_Behaviours_Passive::E_Sleep;
		AgressiveBehaviour = E_Behaviours_Agressive::E_Feral;
	}
};

// --------------------------------------------------

UCLASS()
class THE_HAZARDS_API ATheHazards_GameMode : public AGameModeBase
{
	GENERATED_BODY()

	virtual void StartPlay() override;
};