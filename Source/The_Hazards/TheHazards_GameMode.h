// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TheHazards_GameMode.generated.h"

// --------------------------------------------------

// Enums
// --------------------------------------------------

// Structs
// --------------------------------------------------

USTRUCT()
struct THE_HAZARDS_API FTestStruct
{
	GENERATED_BODY()
};

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

// --------------------------------------------------

UCLASS()
class THE_HAZARDS_API ATheHazards_GameMode : public AGameModeBase
{
	GENERATED_BODY()

	virtual void StartPlay() override;
};