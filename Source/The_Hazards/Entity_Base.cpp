// Fill out your copyright notice in the Description page of Project Settings.


#include "Entity_Base.h"

// Functions
// --------------------------------------------------

// Base actor functions -------------------------

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
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, TEXT("Test: Health and Aura Regen"));
	BaseStats_Current.HealthPoints = 95;
	BaseStats_Current.AuraPoints = 95;

	// Get a reference to the EntityStats proper widget and set the variables
	if(EntityDataWidgetComponent && EntityStatsWidgetComponent_Class) {
		EntityStatsWidgetComponent_Reference = Cast<UBaseClass_WidgetComponent_Entity>(EntityDataWidgetComponent->GetUserWidgetObject());

		if (EntityStatsWidgetComponent_Reference)
			EntityStatsWidgetComponent_Reference->LinkedEntity = this;
	}

	//if (GEngine)
	//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Entity Spawned: Entity_Base"));

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

// Tick functions -------------------------
void AEntity_Base::SetTimers()
{
	// Sprint Penalty timer

	// Health and Aura Regen Delay timers
	GetWorldTimerManager().SetTimer(HealthRegenDelayTimerHandle, this, &AEntity_Base::StartHealthRegenTick, BaseStats_Current.HealthPoints_RegenStartDelay, false);
	GetWorldTimerManager().SetTimer(AuraRegenDelayTimerHandle, this, &AEntity_Base::StartAuraRegenTick, BaseStats_Current.AuraPoints_RegenStartDelay, false);

	// Status Effect Tick timer

	// Attacks timer

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Entity Function: Timers Set"));
}

// Health and Aura functions -------------------------
void AEntity_Base::HealthRegenTick()
{
	if (BaseStats_Current.HealthPoints < BaseStats_Total.HealthPoints) {
		BaseStats_Current.HealthPoints += BaseStats_Current.HealthPoints_RegenPerSecond;
		//GEngine->AddOnScreenDebugMessage(-1, 1.5f, FColor::Green, TEXT("Entity Function: Health Regen Tick"));
	}
}

void AEntity_Base::AuraRegenTick()
{
	if (BaseStats_Current.AuraPoints < BaseStats_Total.AuraPoints) {
		BaseStats_Current.AuraPoints += BaseStats_Current.AuraPoints_RegenPerSecond;
		//GEngine->AddOnScreenDebugMessage(-1, 1.5f, FColor::Green, TEXT("Entity Function: Aura Regen Tick"));
	}
}

void AEntity_Base::StartHealthRegenTick()
{
	GetWorldTimerManager().SetTimer(HealthRegenTimerHandle, this, &AEntity_Base::HealthRegenTick, 1.f, true);
	GetWorldTimerManager().ClearTimer(HealthRegenDelayTimerHandle);
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Entity Function: Start Health Regen Ticks"));
}

void AEntity_Base::StartAuraRegenTick()
{
	GetWorldTimerManager().SetTimer(AuraRegenTimerHandle, this, &AEntity_Base::AuraRegenTick, 1.f, true);
	GetWorldTimerManager().ClearTimer(AuraRegenDelayTimerHandle);
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Entity Function: Start Aura Regen Ticks"));
}

void AEntity_Base::StopHealthRegenTick()
{
	GetWorldTimerManager().SetTimer(HealthRegenDelayTimerHandle, this, &AEntity_Base::StartHealthRegenTick, BaseStats_Current.HealthPoints_RegenStartDelay, false);
	GetWorldTimerManager().ClearTimer(HealthRegenTimerHandle);
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Entity Function: Start Health Regen Delay"));
}

void AEntity_Base::StopAuraRegenTick()
{
	GetWorldTimerManager().SetTimer(AuraRegenDelayTimerHandle, this, &AEntity_Base::StartAuraRegenTick, BaseStats_Current.AuraPoints_RegenStartDelay, false);
	GetWorldTimerManager().ClearTimer(AuraRegenTimerHandle);
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Entity Function: Start Aura Regen Delay"));
}

// Attack functions -------------------------
void AEntity_Base::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherComp && (OtherActor != this) && (Cast<AEntity_Base>(OtherActor)) && (OverlappedComp->GetName().Contains("WeaponCollider") && (OtherComp->GetName().Contains("BoxCollider")) 
		&& !AttackedEntitiesArray.Contains(Cast<AEntity_Base>(OtherActor))))
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Black, TEXT("Overlap Begin  /  Actor: " + this->GetName() + "  /  Other Actor: " + OtherActor->GetName()));
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Black, TEXT("Overlapped Component: " + OverlappedComp->GetName() + "  /  Other Component: " + OtherComp->GetName()));

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
	BaseStats_Current.HealthPoints -= BaseAttackDamage;
	GetWorldTimerManager().ClearTimer(HealthRegenTimerHandle);
	GetWorldTimerManager().SetTimer(HealthRegenDelayTimerHandle, this, &AEntity_Base::StartHealthRegenTick, BaseStats_Current.HealthPoints_RegenStartDelay, false);
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Entity Function: Damage Taken and Health Regen Stopped"));
}