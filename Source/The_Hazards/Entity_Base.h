// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Camera/CameraComponent.h"
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

// Stats -------------------------
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Entity Data")
	F_BaseStats_Struct BaseStats_Current;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Entity Data")
	F_BaseStats_Struct BaseStats_Total;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Entity Data")
	F_SecondaryStats_Struct SecondaryStats;

// Components -------------------------
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* CubeMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UBoxComponent* BoxCollider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* WeaponMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	UBoxComponent* WeaponCollider;

// Timer Handles -------------------------
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

// Technical Variables -------------------------
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Technical Variables")
	TArray<AEntity_Base*> AttackedEntitiesArray;

// Functions
// --------------------------------------------------

// Movement functions -------------------------

// Tick functions -------------------------
	UFUNCTION()
	void SetTimers();

// Health and Aura functions -------------------------
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

// Attack functions
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
