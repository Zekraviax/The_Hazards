// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity_Base.h"


// Functions
// --------------------------------------------------

// ------------------------- Base actor functions

// Sets default values
AEntity_Base::AEntity_Base()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Construct actor components
	CubeMesh = CreateDefaultSubobject<UStaticMeshComponent>("CubeMesh");
	BoxCollider = CreateDefaultSubobject<UBoxComponent>("BoxCollider");
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>("WeaponMesh");
	WeaponCollider = CreateDefaultSubobject<UBoxComponent>("WeaponCollider");
	EntityDataWidgetComponent = CreateDefaultSubobject<UWidgetComponent>("EntityDataWidgetComponent");

	// Attach components
	CubeMesh->SetupAttachment(RootComponent);
	BoxCollider->SetupAttachment(CubeMesh);
	WeaponMesh->SetupAttachment(CubeMesh);
	WeaponCollider->SetupAttachment(WeaponMesh);
	EntityDataWidgetComponent->SetupAttachment(RootComponent);

	//Initialize variables
	MaximumInventorySize = 30;
}

// Called when the game starts or when spawned
void AEntity_Base::BeginPlay()
{
	Super::BeginPlay();

	// Setup Hitbox collisions
	WeaponCollider->SetCollisionProfileName(TEXT("Trigger"));
	WeaponCollider->SetGenerateOverlapEvents(false);
	WeaponCollider->OnComponentBeginOverlap.AddDynamic(this, &AEntity_Base::OnOverlapBegin);

	// Start Timers
	SetTimers();

	// Health and Aura regen test
	CurrentStats.HealthPoints = 75;
	CurrentStats.AuraPoints = 75;

	// Get a reference to the EntityStats proper widget and set the variables
	if(EntityDataWidgetComponent && EntityStatsWidgetComponent_Class) {
		EntityStatsWidgetComponent_Reference = Cast<UBaseClass_WidgetComponent_Entity>(EntityDataWidgetComponent->GetUserWidgetObject());

		if (EntityStatsWidgetComponent_Reference)
			EntityStatsWidgetComponent_Reference->LinkedEntity = this;
	}

	// Spawn a SkillsFunctionLibrary actoir for this entity
	if (SkillsFunctionLibrary_Class) {
		FActorSpawnParameters SpawnInfo;

		SkillsFunctionLibrary_Reference = GetWorld()->SpawnActor<AFunctionLibrary_Skills>(SkillsFunctionLibrary_Class, FVector::ZeroVector, FRotator::ZeroRotator, SpawnInfo);
		SkillsFunctionLibrary_Reference->InitializeSkills();
		SkillsFunctionLibrary_Reference->LinkedEntity = this;
	}
}

// Called every frame
void AEntity_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AEntity_Base::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

// ------------------------- Tick
void AEntity_Base::SetTimers()
{
	// Sprint Penalty timer

	// Health and Aura Regen Delay timers
	GetWorldTimerManager().SetTimer(HealthRegenDelayTimerHandle, this, &AEntity_Base::StartHealthRegenTick, CurrentStats.HealthPoints_RegenStartDelay, false);
	GetWorldTimerManager().SetTimer(AuraRegenDelayTimerHandle, this, &AEntity_Base::StartAuraRegenTick, CurrentStats.AuraPoints_RegenStartDelay, false);

	// Status Effect Tick timer

	// Attacks timer
}

// ------------------------- Health and Aura Timers
void AEntity_Base::HealthRegenTick()
{
	if (CurrentStats.HealthPoints < TotalStats.HealthPoints) {
		CurrentStats.HealthPoints += CurrentStats.HealthPoints_RegenPerSecond;
	}
}

void AEntity_Base::AuraRegenTick()
{
	if (CurrentStats.AuraPoints < TotalStats.AuraPoints) {
		CurrentStats.AuraPoints += CurrentStats.AuraPoints_RegenPerSecond;
	}
}

void AEntity_Base::StartHealthRegenTick()
{
	GetWorldTimerManager().SetTimer(HealthRegenTimerHandle, this, &AEntity_Base::HealthRegenTick, 1.f, true);
	GetWorldTimerManager().ClearTimer(HealthRegenDelayTimerHandle);
}

void AEntity_Base::StartAuraRegenTick()
{
	GetWorldTimerManager().SetTimer(AuraRegenTimerHandle, this, &AEntity_Base::AuraRegenTick, 1.f, true);
	GetWorldTimerManager().ClearTimer(AuraRegenDelayTimerHandle);
}

void AEntity_Base::StopHealthRegenTick()
{
	GetWorldTimerManager().SetTimer(HealthRegenDelayTimerHandle, this, &AEntity_Base::StartHealthRegenTick, CurrentStats.HealthPoints_RegenStartDelay, false);
	GetWorldTimerManager().ClearTimer(HealthRegenTimerHandle);
}

void AEntity_Base::StopAuraRegenTick()
{
	GetWorldTimerManager().SetTimer(AuraRegenDelayTimerHandle, this, &AEntity_Base::StartAuraRegenTick, CurrentStats.AuraPoints_RegenStartDelay, false);
	GetWorldTimerManager().ClearTimer(AuraRegenTimerHandle);
}

// ------------------------- Stats
void AEntity_Base::CalculateTotalStats()
{
	// Step 1: Reset Skill, Item, Temporary Stats
	SkillStats = F_BaseStats_Struct();
	ItemStats = F_BaseStats_Struct();
	TemporaryStats = F_BaseStats_Struct();

	// Step 2: Get all stat changes from Skills
	if (KnownSkills.Num() > 0) {
		for (int i = 0; i < KnownSkills.Num(); i++) {
			if (SkillsFunctionLibrary_Reference && KnownSkills[i].CurrentLevel > 0 && KnownSkills[i].ActivationCondition == E_Skill_ActivationCondition::E_Passive) {
				SkillsFunctionLibrary_Reference->CallSkillFunction(KnownSkills[i].SkillIndex);
			}
		}
	}

	SkillStats.SecondaryStats.MoveSpeed_Multiplier = (SkillStats.SecondaryStats.MoveSpeed_Multiplier / 100) + 1;

	// Step 3: Get all stat changes from Items
	for (F_Item_BaseStruct& Item : Inventory) {
		if (Item.Amount > 0 && Item.IndexInInventoryArray < -10) {
			switch (Item.Supertype) {
			case(E_Item_Supertypes::E_Weapon):
				ItemStats.HealthPoints += Item.Weapon.StatModifiers.HealthPoints;
				ItemStats.HealthPoints_RegenPerSecond += Item.Weapon.StatModifiers.HealthPoints_RegenPerSecond;
				ItemStats.HealthPoints_RegenStartDelay += Item.Weapon.StatModifiers.HealthPoints_RegenStartDelay;
				ItemStats.AuraPoints += Item.Weapon.StatModifiers.AuraPoints;
				ItemStats.AuraPoints_RegenPerSecond += Item.Weapon.StatModifiers.AuraPoints_RegenPerSecond;
				ItemStats.AuraPoints_RegenStartDelay += Item.Weapon.StatModifiers.AuraPoints_RegenStartDelay;
				ItemStats.Physical_Strength += Item.Weapon.StatModifiers.Physical_Strength;
				ItemStats.Physical_Defence += Item.Weapon.StatModifiers.Physical_Defence;
				ItemStats.Elemental_Strength += Item.Weapon.StatModifiers.Elemental_Strength;
				ItemStats.Elemental_Defence += Item.Weapon.StatModifiers.Elemental_Defence;
				ItemStats.Attack_Speed += Item.Weapon.StatModifiers.Attack_Speed;
				ItemStats.Move_Speed += Item.Weapon.StatModifiers.Move_Speed;
				ItemStats.Evasiveness += Item.Weapon.StatModifiers.Evasiveness;
				ItemStats.Status_Potency += Item.Weapon.StatModifiers.Status_Potency;
				ItemStats.Luck += Item.Weapon.StatModifiers.Luck;

				ItemStats.SecondaryStats.Maximum_HealthPoints_Multiplier += Item.Weapon.StatModifiers.SecondaryStats.Maximum_HealthPoints_Multiplier;
				ItemStats.SecondaryStats.HealthPoints_Recovery_Multiplier += Item.Weapon.StatModifiers.SecondaryStats.HealthPoints_Recovery_Multiplier;
				ItemStats.SecondaryStats.HealthPoints_Delay_Multiplier += Item.Weapon.StatModifiers.SecondaryStats.HealthPoints_Delay_Multiplier;
				ItemStats.SecondaryStats.Maximum_AuraPoints_Multiplier += Item.Weapon.StatModifiers.SecondaryStats.Maximum_AuraPoints_Multiplier;
				ItemStats.SecondaryStats.AuraPoints_Recovery_Multiplier += Item.Weapon.StatModifiers.SecondaryStats.AuraPoints_Recovery_Multiplier;
				ItemStats.SecondaryStats.AuraPoints_Delay_Multiplier += Item.Weapon.StatModifiers.SecondaryStats.AuraPoints_Delay_Multiplier;
				ItemStats.SecondaryStats.PhysicalStrength_Multiplier += Item.Weapon.StatModifiers.SecondaryStats.PhysicalStrength_Multiplier;
				ItemStats.SecondaryStats.PhysicalDefence_Multiplier += Item.Weapon.StatModifiers.SecondaryStats.PhysicalDefence_Multiplier;
				ItemStats.SecondaryStats.ElementalStrength_Multiplier += Item.Weapon.StatModifiers.SecondaryStats.ElementalStrength_Multiplier;
				ItemStats.SecondaryStats.AttackSpeed_Multiplier += Item.Weapon.StatModifiers.SecondaryStats.AttackSpeed_Multiplier;
				ItemStats.SecondaryStats.MoveSpeed_Multiplier += Item.Weapon.StatModifiers.SecondaryStats.MoveSpeed_Multiplier;
				ItemStats.SecondaryStats.Evasiveness_Multiplier += Item.Weapon.StatModifiers.SecondaryStats.Evasiveness_Multiplier;
				ItemStats.SecondaryStats.StatusPotency_Multiplier += Item.Weapon.StatModifiers.SecondaryStats.StatusPotency_Multiplier;
				ItemStats.SecondaryStats.Luck_Multiplier += Item.Weapon.StatModifiers.SecondaryStats.Luck_Multiplier;
				ItemStats.SecondaryStats.IncomingDamage_Multiplier += Item.Weapon.StatModifiers.SecondaryStats.IncomingDamage_Multiplier;
				ItemStats.SecondaryStats.OutgoingDamage_Multiplier += Item.Weapon.StatModifiers.SecondaryStats.OutgoingDamage_Multiplier;
				ItemStats.SecondaryStats.Lifesteal_Percentage += Item.Weapon.StatModifiers.SecondaryStats.Lifesteal_Percentage;
				ItemStats.SecondaryStats.StatusDuration_Multiplier += Item.Weapon.StatModifiers.SecondaryStats.StatusDuration_Multiplier;
				ItemStats.SecondaryStats.ShopDiscount_Multiplier += Item.Weapon.StatModifiers.SecondaryStats.ShopDiscount_Multiplier;
				ItemStats.SecondaryStats.Maximum_Companion_Count += Item.Weapon.StatModifiers.SecondaryStats.Maximum_Companion_Count;
				break;
			case(E_Item_Supertypes::E_Armour):
				ItemStats.HealthPoints += Item.Armour.StatModifiers.HealthPoints;
				ItemStats.HealthPoints_RegenPerSecond += Item.Armour.StatModifiers.HealthPoints_RegenPerSecond;
				ItemStats.HealthPoints_RegenStartDelay += Item.Armour.StatModifiers.HealthPoints_RegenStartDelay;
				ItemStats.AuraPoints += Item.Armour.StatModifiers.AuraPoints;
				ItemStats.AuraPoints_RegenPerSecond += Item.Armour.StatModifiers.AuraPoints_RegenPerSecond;
				ItemStats.AuraPoints_RegenStartDelay += Item.Armour.StatModifiers.AuraPoints_RegenStartDelay;
				ItemStats.Physical_Strength += Item.Armour.StatModifiers.Physical_Strength;
				ItemStats.Physical_Defence += Item.Armour.StatModifiers.Physical_Defence;
				ItemStats.Elemental_Strength += Item.Armour.StatModifiers.Elemental_Strength;
				ItemStats.Elemental_Defence += Item.Armour.StatModifiers.Elemental_Defence;
				ItemStats.Attack_Speed += Item.Armour.StatModifiers.Attack_Speed;
				ItemStats.Move_Speed += Item.Armour.StatModifiers.Move_Speed;
				ItemStats.Evasiveness += Item.Armour.StatModifiers.Evasiveness;
				ItemStats.Status_Potency += Item.Armour.StatModifiers.Status_Potency;
				ItemStats.Luck += Item.Armour.StatModifiers.Luck;

				ItemStats.SecondaryStats.Maximum_HealthPoints_Multiplier += Item.Armour.StatModifiers.SecondaryStats.Maximum_HealthPoints_Multiplier;
				ItemStats.SecondaryStats.HealthPoints_Recovery_Multiplier += Item.Armour.StatModifiers.SecondaryStats.HealthPoints_Recovery_Multiplier;
				ItemStats.SecondaryStats.HealthPoints_Delay_Multiplier += Item.Armour.StatModifiers.SecondaryStats.HealthPoints_Delay_Multiplier;
				ItemStats.SecondaryStats.Maximum_AuraPoints_Multiplier += Item.Armour.StatModifiers.SecondaryStats.Maximum_AuraPoints_Multiplier;
				ItemStats.SecondaryStats.AuraPoints_Recovery_Multiplier += Item.Armour.StatModifiers.SecondaryStats.AuraPoints_Recovery_Multiplier;
				ItemStats.SecondaryStats.AuraPoints_Delay_Multiplier += Item.Armour.StatModifiers.SecondaryStats.AuraPoints_Delay_Multiplier;
				ItemStats.SecondaryStats.PhysicalStrength_Multiplier += Item.Armour.StatModifiers.SecondaryStats.PhysicalStrength_Multiplier;
				ItemStats.SecondaryStats.PhysicalDefence_Multiplier += Item.Armour.StatModifiers.SecondaryStats.PhysicalDefence_Multiplier;
				ItemStats.SecondaryStats.ElementalStrength_Multiplier += Item.Armour.StatModifiers.SecondaryStats.ElementalStrength_Multiplier;
				ItemStats.SecondaryStats.AttackSpeed_Multiplier += Item.Armour.StatModifiers.SecondaryStats.AttackSpeed_Multiplier;
				ItemStats.SecondaryStats.MoveSpeed_Multiplier += Item.Armour.StatModifiers.SecondaryStats.MoveSpeed_Multiplier;
				ItemStats.SecondaryStats.Evasiveness_Multiplier += Item.Armour.StatModifiers.SecondaryStats.Evasiveness_Multiplier;
				ItemStats.SecondaryStats.StatusPotency_Multiplier += Item.Armour.StatModifiers.SecondaryStats.StatusPotency_Multiplier;
				ItemStats.SecondaryStats.Luck_Multiplier += Item.Armour.StatModifiers.SecondaryStats.Luck_Multiplier;
				ItemStats.SecondaryStats.IncomingDamage_Multiplier += Item.Armour.StatModifiers.SecondaryStats.IncomingDamage_Multiplier;
				ItemStats.SecondaryStats.OutgoingDamage_Multiplier += Item.Armour.StatModifiers.SecondaryStats.OutgoingDamage_Multiplier;
				ItemStats.SecondaryStats.Lifesteal_Percentage += Item.Armour.StatModifiers.SecondaryStats.Lifesteal_Percentage;
				ItemStats.SecondaryStats.StatusDuration_Multiplier += Item.Armour.StatModifiers.SecondaryStats.StatusDuration_Multiplier;
				ItemStats.SecondaryStats.ShopDiscount_Multiplier += Item.Armour.StatModifiers.SecondaryStats.ShopDiscount_Multiplier;
				ItemStats.SecondaryStats.Maximum_Companion_Count += Item.Armour.StatModifiers.SecondaryStats.Maximum_Companion_Count;
				break;
			}
		}
	}

	ItemStats.SecondaryStats.MoveSpeed_Multiplier = (ItemStats.SecondaryStats.MoveSpeed_Multiplier / 100) + 1;

	// Step 4: Get all stat changes from Temporary sources

	// Step 5: Set (Total = Level * Skill * Item) Stats

	// Set entity movespeed
	TotalStats.Move_Speed = ((LevelStats.Move_Speed * LevelStats.SecondaryStats.MoveSpeed_Multiplier) +
		(SkillStats.Move_Speed * SkillStats.SecondaryStats.MoveSpeed_Multiplier) +
		(ItemStats.Move_Speed * ItemStats.SecondaryStats.MoveSpeed_Multiplier));

	// Step 6: Set (Current = Total * Temporary) Stats
	CurrentStats.Move_Speed = (TotalStats.Move_Speed + (TemporaryStats.Move_Speed * TemporaryStats.SecondaryStats.MoveSpeed_Multiplier));

	// Step 7: Assign Variables such as MaxWalkSpeed
	GetCharacterMovement()->MaxWalkSpeed = TotalStats.Move_Speed;
}

// ------------------------- Attack
void AEntity_Base::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherComp && (OtherActor != this) && (Cast<AEntity_Base>(OtherActor)) && (OverlappedComp->GetName().Contains("WeaponCollider") && (OtherComp->GetName().Contains("BoxCollider")) 
		&& !AttackedEntitiesArray.Contains(Cast<AEntity_Base>(OtherActor))))
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("Overlap Begin  /  Actor: " + this->GetName() + "  /  Other Actor: " + OtherActor->GetName()));
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, TEXT("Overlapped Component: " + OverlappedComp->GetName() + "  /  Other Component: " + OtherComp->GetName()));

		AttackedEntitiesArray.Add(Cast<AEntity_Base>(OtherActor));
		Cast<AEntity_Base>(OtherActor)->EntityHit(20);
	}
}

void AEntity_Base::AttackStart()
{
	if (!GetWorldTimerManager().IsTimerActive(AttackSwingTimerHandle)) {
		WeaponCollider->SetGenerateOverlapEvents(true);
		GetWorldTimerManager().SetTimer(AttackSwingTimerHandle, this, &AEntity_Base::AttackEnd, 1.5f, false);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Attack Start"));
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Attack Timer Counting Down"));
	}
}

void AEntity_Base::AttackEnd()
{
	WeaponCollider->SetGenerateOverlapEvents(false);
	GetWorldTimerManager().ClearTimer(AttackSwingTimerHandle);
	AttackedEntitiesArray.Empty();
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TEXT("Attack End"));
}

void AEntity_Base::EntityHit(int32 BaseAttackDamage)
{
	CurrentStats.HealthPoints -= BaseAttackDamage;
	GetWorldTimerManager().ClearTimer(HealthRegenTimerHandle);
	GetWorldTimerManager().SetTimer(HealthRegenDelayTimerHandle, this, &AEntity_Base::StartHealthRegenTick, CurrentStats.HealthPoints_RegenStartDelay, false);
}