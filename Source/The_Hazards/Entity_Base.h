// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EngineUtils.h"
#include "Engine/DataTable.h"
#include "BaseClass_WidgetComponent_Entity.h"
#include "FunctionLibrary_Skills.h"
#include "TheHazards_GameMode.h"

#include "Entity_Base.generated.h"

UCLASS()
class THE_HAZARDS_API AEntity_Base : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEntity_Base();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

// Base Variables
// --------------------------------------------------

// ------------------------- Character
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Entity")
	F_Entity_CharacterSheet CharacterSheet;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Entity")
	int32 Level;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Entity")
	int32 Money;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Entity")
	int32 Scrap;

// ------------------------- Stats
	// Combined totals of all other Stats variables, except CurrentStats.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	F_BaseStats_Struct TotalStats;

	// Total Stats combined with temporary stat changes (e.g status effects, buffs, etc.)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	F_BaseStats_Struct CurrentStats;

	// Stats gained solely from leveling up.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	F_BaseStats_Struct LevelStats;

	// Stats gained from levelling up skills. Must be re-calculated everytime a skill is leveled.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	F_BaseStats_Struct SkillStats;

	// Stats gained from equipping items. Must be re-calculated everytine an item is equipped or unequipped.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	F_BaseStats_Struct ItemStats;

	// Temporary stat changes (e.g status effects, buffs, etc.) Must be recalculated constantly.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	F_BaseStats_Struct TemporaryStats;

// ------------------------- Inventory
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TArray<F_Item_BaseStruct> Inventory;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	int32 MaximumInventorySize;

// ------------------------- Skills
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skills")
	TSubclassOf<AFunctionLibrary_Skills> SkillsFunctionLibrary_Class;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skills")
	AFunctionLibrary_Skills* SkillsFunctionLibrary_Reference;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Skills")
	TArray<F_Skill_Base> KnownSkills;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Skills")
	int32 UnspentSkillPoints;

// ------------------------- Components
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* CubeMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UBoxComponent* BoxCollider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* WeaponMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UBoxComponent* WeaponCollider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UWidgetComponent* EntityDataWidgetComponent;

// ------------------------- Widgets
	UPROPERTY(visibleAnywhere, BlueprintReadOnly, Category = "Widgets")
	UBaseClass_WidgetComponent_Entity* EntityStatsWidgetComponent_Reference;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<UBaseClass_WidgetComponent_Entity> EntityStatsWidgetComponent_Class;

// ------------------------- Timer Handles
	UPROPERTY()
	FTimerHandle HealthRegenTimerHandle;

	UPROPERTY()
	FTimerHandle AuraRegenTimerHandle;

	UPROPERTY()
	FTimerHandle HealthRegenDelayTimerHandle;

	UPROPERTY()
	FTimerHandle AuraRegenDelayTimerHandle;

	UPROPERTY()
	FTimerHandle StatusEffectTickTimerHandle;

	UPROPERTY()
	FTimerHandle AttackSwingTimerHandle;

// ------------------------- Technical Variables
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Technical Variables")
	TArray<AEntity_Base*> AttackedEntitiesArray;

// Functions
// --------------------------------------------------

// ------------------------- Movement

// ------------------------- Tick
	UFUNCTION()
	void SetTimers();

// ------------------------- Health and Aura
	UFUNCTION(BlueprintCallable)
	void HealthRegenTick();

	UFUNCTION(BlueprintCallable)
	void AuraRegenTick();

	UFUNCTION(BlueprintCallable)
	void StartHealthRegenTick();

	UFUNCTION(BlueprintCallable)
	void StartAuraRegenTick();

	UFUNCTION(BlueprintCallable)
	void StopHealthRegenTick();

	UFUNCTION(BlueprintCallable)
	void StopAuraRegenTick();

// ------------------------- Stats
	UFUNCTION()
	void CalculateTotalStats();

// ------------------------- Attack Functions
	// Weapon hitbox overlap
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void AttackStart();

	UFUNCTION()
	void AttackEnd();

	// Entity received damage function
	UFUNCTION()
	void EntityHit(int32 BaseAttackDamage);
};
