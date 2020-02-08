#include "Entity_Base.h"

#include "Entity_Player.h"
#include "SubWidget_StatusEffectIcon.h"


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
	RotatingCore = CreateDefaultSubobject<USceneComponent>("RotatingCore");
	EntityDataWidgetComponent = CreateDefaultSubobject<UWidgetComponent>("EntityDataWidgetComponent");

	// Construct Timeline
	const ConstructorHelpers::FObjectFinder<UCurveFloat> Curve(TEXT("CurveFloat'/Game/DataCurves/Melee_Swing_Curve.Melee_Swing_Curve'"));
	if (Curve.Object)
		AttackAnimationFloatCurve = Curve.Object;

	// Attach components
	CubeMesh->SetupAttachment(RootComponent);
	BoxCollider->SetupAttachment(CubeMesh);
	RotatingCore->SetupAttachment(CubeMesh);
	WeaponMesh->SetupAttachment(RotatingCore);
	WeaponCollider->SetupAttachment(WeaponMesh);
	EntityDataWidgetComponent->SetupAttachment(RootComponent);

	//Initialize variables
	MaximumInventorySize = 30;

	// Set Stats
	SkillStats.Move_Speed = 1;
	ItemStats.Move_Speed = 1;
	TemporaryStats.Move_Speed = 1;
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

	// Finish creating timelines
	if (AttackAnimationFloatCurve != NULL) {
		// Variables
		FOnTimelineFloat PlayFunction;
		FOnTimelineEventStatic FinishFunction;

		AttackAnimationTimeline = NewObject<UTimelineComponent>(this, FName("AttackTimelineAnimationComponent"));

		AttackAnimationTimeline->SetLooping(false);
		AttackAnimationTimeline->SetTimelineLength(1.f);
		AttackAnimationTimeline->SetPlaybackPosition(0.f, false);
		AttackAnimationTimeline->SetPlayRate(0.5f);

		PlayFunction.BindUFunction(this, "PlayAttackAnimation");
		FinishFunction.BindUFunction(this, "FinishAttackAnimation");
		AttackAnimationTimeline->AddInterpFloat(AttackAnimationFloatCurve, PlayFunction);
		//AttackAnimationTimeline->SetTimelineFinishedFunc(FinishAttackAnimation);

		AttackAnimationTimeline->RegisterComponent();
	}

	// Health and Aura regen test
	CurrentStats.HealthPoints = 75;
	CurrentStats.AuraPoints = 75;

	// Get a reference to the EntityStats proper widget and set the variables
	if(EntityDataWidgetComponent && EntityStatsWidgetComponent_Class) {
		EntityStatsWidgetComponent_Reference = Cast<UBaseClass_WidgetComponent_Entity>(EntityDataWidgetComponent->GetUserWidgetObject());

		if (EntityStatsWidgetComponent_Reference)
			EntityStatsWidgetComponent_Reference->LinkedEntity = this;
	}

	// Spawn a SkillsFunctionLibrary actor for this entity
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

	// Tick Timelines
	if (AttackAnimationTimeline != NULL) {
		AttackAnimationTimeline->TickComponent(DeltaTime, ELevelTick::LEVELTICK_TimeOnly, NULL);
	}

	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, FString::Printf(TEXT("Delta Time: %f"), DeltaTime));

	// Tick Status Effects
	if (StatusEffectsArray.Num() > 0) {
		for (int i = 0; i < StatusEffectsArray.Num(); i++) {
			//GEngine->AddOnScreenDebugMessage(-1, 0.15f, FColor::Yellow, FString::Printf(TEXT("Update Status Time: %f"), StatusEffectsArray[i].CurrentTime));

			// Increment Time
			StatusEffectsArray[i].CurrentTime -= DeltaTime;

			// If time has reach 1 or move, remove a Stack
			if (StatusEffectsArray[i].CurrentTime <= 0) {
				StatusEffectsArray[i].CurrentTime = 1;
				StatusEffectsArray[i].CurrentStackCount--;
			}

			// if this is a Player, update the Player's Widgets
			if (Cast<AEntity_Player>(this)) {
				Cast<AEntity_Player>(this)->UpdateStatusEffectWidgets();
			}

			// If Stacks have reached 0, remove Status Effect
			if (StatusEffectsArray[i].CurrentStackCount <= 0) {
				StatusEffectsArray.RemoveAt(i);
			}
		}
	}

	// Add force if Dodging
}

// Called to bind functionality to input
void AEntity_Base::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

// ------------------------- Tick and Timers
void AEntity_Base::SetTimers()
{
	// Sprint Penalty timer

	// Health and Aura Regen Delay timers
	GetWorldTimerManager().SetTimer(HealthRegenDelayTimerHandle, this, &AEntity_Base::StopHealthRegenTick, CurrentStats.HealthPoints_RegenStartDelay, false);
	GetWorldTimerManager().SetTimer(AuraRegenDelayTimerHandle, this, &AEntity_Base::StopAuraRegenTick, CurrentStats.AuraPoints_RegenStartDelay, false);

	// Status Effect Tick timer

	// Attacks timer
}

// Health and Aura Timers
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

// Sprint Penalty Timer
void::AEntity_Base::SprintPenaltyTick()
{
	if (CurrentStats.AuraPoints > 0) {
		CurrentStats.AuraPoints -= 0.5;
	} else {
		Sprint();
	}
}

void AEntity_Base::DodgeTick()
{
	GetWorldTimerManager().ClearTimer(DodgeTimerHandle);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Dodge Tick"));
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
	// Health
	TotalStats.HealthPoints = ((LevelStats.HealthPoints * LevelStats.SecondaryStats.Maximum_HealthPoints_Multiplier) *
		(SkillStats.HealthPoints * SkillStats.SecondaryStats.Maximum_HealthPoints_Multiplier) *
		(ItemStats.HealthPoints * ItemStats.SecondaryStats.Maximum_HealthPoints_Multiplier));
	TotalStats.HealthPoints_RegenPerSecond = LevelStats.HealthPoints_RegenPerSecond * SkillStats.HealthPoints_RegenPerSecond * ItemStats.HealthPoints_RegenPerSecond;
	TotalStats.HealthPoints_RegenStartDelay = ((LevelStats.HealthPoints_RegenStartDelay * LevelStats.SecondaryStats.HealthPoints_Delay_Multiplier) *
		(SkillStats.HealthPoints_RegenStartDelay * SkillStats.SecondaryStats.HealthPoints_Delay_Multiplier) *
		(ItemStats.HealthPoints_RegenStartDelay * ItemStats.SecondaryStats.HealthPoints_Delay_Multiplier));
	// Aura
	TotalStats.AuraPoints = ((LevelStats.AuraPoints * LevelStats.SecondaryStats.Maximum_AuraPoints_Multiplier) *
		(SkillStats.AuraPoints * SkillStats.SecondaryStats.Maximum_AuraPoints_Multiplier) *
		(ItemStats.AuraPoints * ItemStats.SecondaryStats.Maximum_AuraPoints_Multiplier));
	TotalStats.AuraPoints_RegenPerSecond = LevelStats.AuraPoints_RegenPerSecond * SkillStats.AuraPoints_RegenPerSecond * ItemStats.AuraPoints_RegenPerSecond;
	TotalStats.AuraPoints_RegenStartDelay = ((LevelStats.AuraPoints_RegenStartDelay * LevelStats.SecondaryStats.AuraPoints_Delay_Multiplier) *
		(SkillStats.AuraPoints_RegenStartDelay * SkillStats.SecondaryStats.AuraPoints_Delay_Multiplier) *
		(ItemStats.AuraPoints_RegenStartDelay * ItemStats.SecondaryStats.AuraPoints_Delay_Multiplier));
	// Stats
	TotalStats.Physical_Strength = ((LevelStats.Physical_Strength * LevelStats.SecondaryStats.PhysicalStrength_Multiplier) *
		(SkillStats.Physical_Strength * SkillStats.SecondaryStats.PhysicalStrength_Multiplier) *
		(ItemStats.Physical_Strength * ItemStats.SecondaryStats.PhysicalStrength_Multiplier));
	TotalStats.Physical_Defence = ((LevelStats.Physical_Defence * LevelStats.SecondaryStats.PhysicalDefence_Multiplier) *
		(SkillStats.Physical_Defence * SkillStats.SecondaryStats.PhysicalDefence_Multiplier) *
		(ItemStats.Physical_Defence * ItemStats.SecondaryStats.PhysicalDefence_Multiplier));
	TotalStats.Elemental_Strength = ((LevelStats.Elemental_Strength * LevelStats.SecondaryStats.ElementalStrength_Multiplier) *
		(SkillStats.Elemental_Strength * SkillStats.SecondaryStats.ElementalStrength_Multiplier) *
		(ItemStats.Elemental_Strength * ItemStats.SecondaryStats.ElementalStrength_Multiplier));
	TotalStats.Elemental_Defence = ((LevelStats.Elemental_Defence * LevelStats.SecondaryStats.ElementalDefence_Multiplier) *
		(SkillStats.Elemental_Defence * SkillStats.SecondaryStats.ElementalDefence_Multiplier) *
		(ItemStats.Elemental_Defence * ItemStats.SecondaryStats.ElementalDefence_Multiplier));
	TotalStats.Attack_Speed = ((LevelStats.Attack_Speed * LevelStats.SecondaryStats.AttackSpeed_Multiplier) *
		(SkillStats.Attack_Speed * SkillStats.SecondaryStats.AttackSpeed_Multiplier) *
		(ItemStats.Attack_Speed * ItemStats.SecondaryStats.AttackSpeed_Multiplier));
	TotalStats.Move_Speed = ((LevelStats.Move_Speed * LevelStats.SecondaryStats.MoveSpeed_Multiplier) *
		(SkillStats.Move_Speed * SkillStats.SecondaryStats.MoveSpeed_Multiplier) *
		(ItemStats.Move_Speed * ItemStats.SecondaryStats.MoveSpeed_Multiplier));
	TotalStats.Evasiveness = ((LevelStats.Evasiveness * LevelStats.SecondaryStats.Evasiveness_Multiplier) *
		(SkillStats.Evasiveness * SkillStats.SecondaryStats.Evasiveness_Multiplier) *
		(ItemStats.Evasiveness * ItemStats.SecondaryStats.Evasiveness_Multiplier));
	TotalStats.Status_Potency = ((LevelStats.Status_Potency * LevelStats.SecondaryStats.StatusPotency_Multiplier) *
		(SkillStats.Status_Potency * SkillStats.SecondaryStats.StatusPotency_Multiplier) *
		(ItemStats.Status_Potency * ItemStats.SecondaryStats.StatusPotency_Multiplier));
	TotalStats.Luck = ((LevelStats.Luck * LevelStats.SecondaryStats.Luck_Multiplier) *
		(SkillStats.Luck * SkillStats.SecondaryStats.Luck_Multiplier) *
		(ItemStats.Luck * ItemStats.SecondaryStats.Luck_Multiplier));

	// Step 6: Set (Current = Total * Temporary) Stats
	//CurrentStats.HealthPoints = (TotalStats.HealthPoints * (TemporaryStats.HealthPoints * TemporaryStats.SecondaryStats.Maximum_HealthPoints_Multiplier));
	CurrentStats.Move_Speed = (TotalStats.Move_Speed * (TemporaryStats.Move_Speed * TemporaryStats.SecondaryStats.MoveSpeed_Multiplier));

	// Step 7: Assign Unreal Engine Variables such as MaxWalkSpeed
	// (Multiply by x2 or x.5 if Sneaking or Sprinting)
	if (IsSprinting)
		GetCharacterMovement()->MaxWalkSpeed = TotalStats.Move_Speed * 2;
	else if (IsSneaking)
		GetCharacterMovement()->MaxWalkSpeed = TotalStats.Move_Speed * 0.5;
	else
		GetCharacterMovement()->MaxWalkSpeed = TotalStats.Move_Speed;
}

// ------------------------- Movement
void AEntity_Base::Sprint()
{
	if (IsSneaking)
		IsSneaking = false;

	IsSprinting = !IsSprinting;

	// Start Sprinting
	if (IsSprinting) {
		GetWorldTimerManager().SetTimer(SprintPenaltyTimerHandle, this, &AEntity_Base::SprintPenaltyTick, 1.f, true);
		// Stop Aura Regen while sprinting
		GetWorldTimerManager().ClearTimer(AuraRegenTimerHandle);
	} else {
		GetWorldTimerManager().SetTimer(AuraRegenDelayTimerHandle, this, &AEntity_Base::StartAuraRegenTick, CurrentStats.AuraPoints_RegenStartDelay, false);
		GetWorldTimerManager().ClearTimer(SprintPenaltyTimerHandle);
	}

	CalculateTotalStats();
}

void AEntity_Base::Sneak()
{
	if (IsSprinting)
		IsSprinting = false;

	IsSneaking = !IsSneaking;
	CalculateTotalStats();
}

void AEntity_Base::Dodge()
{
	GetWorldTimerManager().SetTimer(DodgeTimerHandle, this, &AEntity_Base::DodgeTick, 1.f, true);

	if (StatusEffectsDataTable_Reference) {
		FString ContextString;
		F_StatusEffect_Base* DodgeStatus = StatusEffectsDataTable_Reference->FindRow<F_StatusEffect_Base>(FName(TEXT("Dodge")), ContextString, true);
		AddStatusEffect(*DodgeStatus);
	}
}

// ------------------------- Status Effects
void AEntity_Base::AddStatusEffect(F_StatusEffect_Base StatusEffect)
{
	AEntity_Player* PlayerCast = Cast<AEntity_Player>(this);

	// If this is a player, create a status effect icon
	if (PlayerCast) {
		PlayerCast->StatusEffectsArray.Add(StatusEffect);
		PlayerCast->CreateStatusEffectWidget(StatusEffect);
	} else {
		StatusEffectsArray.Add(StatusEffect);
	}
}

// ------------------------- Attack
void AEntity_Base::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherComp && (OtherActor != this) && (Cast<AEntity_Base>(OtherActor)) && (OverlappedComp->GetName().Contains("WeaponCollider") && (OtherComp->GetName().Contains("BoxCollider")) && !AttackedEntitiesArray.Contains(Cast<AEntity_Base>(OtherActor))))
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
		GetWorldTimerManager().SetTimer(AttackSwingTimerHandle, this, &AEntity_Base::AttackEnd, 1.f, false);

		if (AttackAnimationTimeline != NULL) {
			//AttackAnimationTimeline->SetPlayRate(0.5);
			AttackAnimationTimeline->PlayFromStart();
		}

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

void AEntity_Base::PlayAttackAnimation(float Value)
{
	float OriginalYaw = 0;
	//UE_LOG(LogTemp, Warning, TEXT("Play Attack Animation  /  Yaw Value: %f  /  Timeline Value: %f  /  Calculated Yaw: %f  /  Original Yaw: %f"), RotatingCore->RelativeRotation.Yaw, Value, (OriginalYaw - Value), OriginalYaw);
	RotatingCore->SetRelativeRotation(FRotator(0, Value, 0).Quaternion());
}

void AEntity_Base::FinishAttackAnimation()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Finish Attack Animation"));
}

void AEntity_Base::EntityHit(int32 BaseAttackDamage)
{
	CurrentStats.HealthPoints -= BaseAttackDamage;
	GetWorldTimerManager().ClearTimer(HealthRegenTimerHandle);
	GetWorldTimerManager().SetTimer(HealthRegenDelayTimerHandle, this, &AEntity_Base::StartHealthRegenTick, CurrentStats.HealthPoints_RegenStartDelay, false);
}