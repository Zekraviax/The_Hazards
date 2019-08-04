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

	// Attach components
	CubeMesh->SetupAttachment(RootComponent);
	BoxCollider->SetupAttachment(CubeMesh);
	WeaponMesh->SetupAttachment(CubeMesh);
	WeaponCollider->SetupAttachment(WeaponMesh);
}

// Called when the game starts or when spawned
void AEntity_Base::BeginPlay()
{
	Super::BeginPlay();

	// Setup Hitbox collisions
	//BoxCollider->SetCollisionProfileName(TEXT("Trigger"));
	//BoxCollider->SetGenerateOverlapEvents(true);
	//BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &AEntity_Base::OnOverlapBegin);
	WeaponCollider->SetCollisionProfileName(TEXT("Trigger"));
	WeaponCollider->SetGenerateOverlapEvents(true);
	WeaponCollider->OnComponentBeginOverlap.AddDynamic(this, &AEntity_Base::OnOverlapBegin);

	// Start Timers
	SetTimers();

	// Health and Aura regen test
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, TEXT("Test: Health and Aura Regen"));
	BaseStats_Current.HealthPoints = 95;
	BaseStats_Current.AuraPoints = 95;

	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Entity Spawned: Entity_Base"));

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

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Entity Function: Timers Set"));
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
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Entity Function: Start Health Regen Ticks"));
}

void AEntity_Base::StartAuraRegenTick()
{
	GetWorldTimerManager().SetTimer(AuraRegenTimerHandle, this, &AEntity_Base::AuraRegenTick, 1.f, true);
	GetWorldTimerManager().ClearTimer(AuraRegenDelayTimerHandle);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Entity Function: Start Aura Regen Ticks"));
}

void AEntity_Base::StopHealthRegenTick()
{
	GetWorldTimerManager().SetTimer(HealthRegenDelayTimerHandle, this, &AEntity_Base::StartHealthRegenTick, BaseStats_Current.HealthPoints_RegenStartDelay, false);
	GetWorldTimerManager().ClearTimer(HealthRegenTimerHandle);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Entity Function: Start Health Regen Delay"));
}

void AEntity_Base::StopAuraRegenTick()
{
	GetWorldTimerManager().SetTimer(AuraRegenDelayTimerHandle, this, &AEntity_Base::StartAuraRegenTick, BaseStats_Current.AuraPoints_RegenStartDelay, false);
	GetWorldTimerManager().ClearTimer(AuraRegenTimerHandle);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Entity Function: Start Aura Regen Delay"));
}

// Attack functions -------------------------
void AEntity_Base::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherComp && (OtherActor != this) && (OverlappedComp->GetName().Contains("WeaponCollider") && (OtherComp->GetName().Contains("BoxCollider"))))
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Black, TEXT("Overlap Begin  /  Actor: " + this->GetName() + "  /  Other Actor: " + OtherActor->GetName()));
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Black, TEXT("Overlapped Component: " + OverlappedComp->GetName() + "  /  Other Component: " + OtherComp->GetName()));
	}
	//if (OtherActor != this) {
	//	//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Black, TEXT("Actor: " + this->GetName()));
	//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Black, TEXT("Overlapped Actor: " + OtherActor->GetName()));
	//}
	//else {
	//	GEngine->AddOnScreenDebugMessage(-1, 0.05f, FColor::Red, TEXT("Actor: " + this->GetName()));
	//}
}