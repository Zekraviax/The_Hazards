#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/TimelineComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EngineUtils.h"
#include "Engine/DataTable.h"
#include "DrawDebugHelpers.h"
#include "BaseClass_WidgetComponent_Entity.h"
#include "FunctionLibrary_Skills.h"
#include "FunctionLibrary_SpecialAttacks.h"
#include "TheHazards_GameMode.h"

#include "Entity_Base.generated.h"

// Forward Declarations
class AEntity_Item;


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

// ------------------------- Entity
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Entity")
	F_Entity_CharacterSheet CharacterSheet;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Entity")
	int32 Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Entity")
	int32 Experience;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Entity")
	int32 Money;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Entity")
	int32 Scrap;

// ------------------------- Movement
	UPROPERTY()
	bool IsDodging;

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

	// Temporary stat changes (e.g status effects, buffs, etc.) Must be recalculated near-constantly.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	F_BaseStats_Struct TemporaryStats;

// ------------------------- Inventory
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	TArray<F_Item_BaseStruct> Inventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	int32 MaximumInventorySize;

	// All Entities need Equipment for attacking, at least a Primary Weapon
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	F_Item_BaseStruct PrimaryWeapon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	F_Item_BaseStruct SecondaryWeapon;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	F_Item_BaseStruct TertiaryWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	F_Item_BaseStruct HeadArmour;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	F_Item_BaseStruct BodyArmour;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	F_Item_BaseStruct LegArmour;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inventory")
	F_Item_BaseStruct CurrentEquippedWeapon;

// ------------------------- Skills
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skills")
	TSubclassOf<AFunctionLibrary_Skills> SkillsFunctionLibrary_Class;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skills")
	AFunctionLibrary_Skills* SkillsFunctionLibrary_Reference;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Skills")
	TArray<F_Skill_Base> KnownSkills;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Skills")
	int32 UnspentSkillPoints;

// ------------------------- Special Attacks
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Special Attacks")
	TSubclassOf<AFunctionLibrary_SpecialAttacks> SpecialAttacksFunctionLibrary_Class;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Special Attacks")
	AFunctionLibrary_SpecialAttacks* SpecialAttacksFunctionLibrary_Reference;

// ------------------------- Status Effects
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status Effects")
	UDataTable* StatusEffectsDataTable_Reference;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Status Effects")
	TArray<F_StatusEffect_Base> StatusEffectsArray;

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
	USceneComponent* RotatingCore;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UWidgetComponent* EntityDataWidgetComponent;

// ------------------------- Widgets
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<UBaseClass_WidgetComponent_Entity> EntityStatsWidgetComponent_Class;

	UPROPERTY(visibleAnywhere, BlueprintReadOnly, Category = "Widgets")
	UBaseClass_WidgetComponent_Entity* EntityStatsWidgetComponent_Reference;

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
	FTimerHandle SprintPenaltyTimerHandle;

	UPROPERTY()
	FTimerHandle DodgeTimerHandle;

	//UPROPERTY()
	//FTimerHandle StatusEffectTickTimerHandle;

	UPROPERTY()
	FTimerHandle AttackSwingTimerHandle;

	UPROPERTY()
	FTimerHandle SpecialAttackSwingTimerHandle;

// ------------------------- Technical Variables
	// Used to prevent a single entity from being hit multiple times in a single attack
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Technical Variables")
	TArray<AEntity_Base*> AttackedEntitiesArray;

	UPROPERTY()
	UTimelineComponent* AttackAnimationTimeline;

	UPROPERTY()
	UCurveFloat* AttackAnimationFloatCurve;

	// Movement
	UPROPERTY()
	bool IsSprinting;

	UPROPERTY()
	bool IsSneaking;

	UPROPERTY()
	bool CanAttack;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Technical Variables")
	TSubclassOf<AEntity_Item> Item_Class;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Technical Variables")
	AEntity_Item* Item_Reference;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Technical Variables")
	int ExperienceGivenOnDeath;

// Functions
// --------------------------------------------------

// ------------------------- Timers
	UFUNCTION()
	void SetTimers();

	// Health and Aura
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

	// Sprint Penalty
	UFUNCTION()
	void SprintPenaltyTick();

	// Dodge
	UFUNCTION()
	void DodgeTick();

// ------------------------- Stats
	UFUNCTION()
	void CalculateTotalStats();

// ------------------------- Movement
	UFUNCTION()
	void Sprint();

	UFUNCTION()
	void Sneak();

	UFUNCTION()
	void Dodge();

// ------------------------- Status Effects
	UFUNCTION()
	void AddStatusEffect(F_StatusEffect_Base StatusEffect);

// ------------------------- Attack
	// Weapon hitbox overlap
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void AttackStart();

	UFUNCTION()
	void AttackEnd();

	UFUNCTION()
	void SpecialAttackStart();

	UFUNCTION()
	void SpecialAttackEnd();

	UFUNCTION()
	void PlayAttackAnimation(float Value);

	UFUNCTION()
	void FinishAttackAnimation();

	// Entity received damage function
	UFUNCTION()
	void EntityHit(int32 BaseAttackDamage);

	UFUNCTION()
	void EntityDeath(bool GrantExperienceToPlayer, AEntity_Player* PlayerReference = NULL);

// ------------------------- Inventory
	UFUNCTION()
	void AddItemToInventory(F_Item_BaseStruct ItemToAdd);
};
