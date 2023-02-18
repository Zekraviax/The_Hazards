#pragma once


#include "CoreMinimal.h"

#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"
#include "TheHazardsPlayerController.h"

#include "EntityBaseCharacter.generated.h"


class UActorComponentBaseStats;
class UActorComponentInventory;
class UInputComponent;
class UWidgetHudBattle;


UCLASS(config=Game)
class AEntityBaseCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Replicated, Category = Mesh)
	class USkeletalMeshComponent* Mesh1P;

	/** Gun mesh: 1st person view (seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Replicated, Category = Mesh)
	class USkeletalMeshComponent* FP_Gun;

	/** Location on gun mesh where projectiles should spawn. */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USceneComponent* FP_MuzzleLocation;

	// Entity's statistics
	UPROPERTY(VisibleDefaultsOnly, Category = Gameplay)
	UActorComponentBaseStats* BaseStatsComponent;

	// Holds the entity's items
	UPROPERTY(VisibleDefaultsOnly, Category = Gameplay)
	UActorComponentInventory* InventoryComponent;

public:
	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCameraComponent;

	// Constructor
	AEntityBaseCharacter();

	// Function needed to replicate things in multiplayer
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

protected:
	virtual void BeginPlay();


public:
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	float BaseLookUpRate;

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector GunOffset;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class USoundBase* FireSound;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class UAnimMontage* FireAnimation;

	// TimerHandle for automatically firing a weapon
	FTimerHandle AutomaticWeaponFireTimerHandle;

	// Used to position the camera off the ground
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float CharacterHeight = 64.f;

	// Used in changing and reseting the entity's move speed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float BaseMoveSpeed = 600.f;

	// Used in the tick function to adjust the camera height
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gameplay)
	bool IsCrouching = false;

	// Used in the tick function to drain Aura Points
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gameplay)
	bool IsSprinting = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gameplay)
	bool IsCharging = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gameplay)
	FTimerHandle BeginChargeTimerHandle;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gameplay)
	FTimerHandle ChargeTimerHandle;

	// Used for crouching in the Tick() function
	float LerpValue;

	// Used for values that are adjusted over time in the Tick() function,
	// such as crouch height and HP/AP regeneration per tick
	float LerpRate = 0.05f;

	/** Fires a projectile. */
	void OnFire();

	// Clear any automatic firing TimerHandles when the fire button is de-pressed
	void OnStopFiring();

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	void MoveRight(float Val);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	// Our implementation of the function allows us to dynamically change the turn rate
	// e.g. when charging, the turn and look at rates should be very low
	// yaw input is for left/right turning
	void EntityAddYawInput(float Val);

	// pitch input is for up/down turning
	void EntityAddPitchInput(float Val);

	// On begin crouching, reduce the camera position by half
	void OnCrouchBegin();

	// On end crouching, return the camera position to normal height
	void OnCrouchEnd();

	// On begin sprinting, increase the entity's base move speed by 50%
	void OnSprintBegin();

	// On end sprinting, return the entity's base move speed to normal
	void OnSprintEnd();

	// If the player is sprinting when they jump, launch them forward as a Long Jump
	void OnJumpBegin();

	// Special movements
	void OnChargeBeginHeldDown();

	void OnChargeEndHeldDown();

	void OnChargeTimerReachedZero();

	/**
	 * Function called when something hurts this entity
	 * @param Damage	Result of damage formula from attacker
	 * @param Source	Whichever entity is attacking
	 */
	void ReceiveDamage(float Damage, AEntityBaseCharacter* Source);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** Returns Mesh1P subobject **/
	FORCEINLINE class USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }
	// Return entity's BaseStatsComponent
	FORCEINLINE class UActorComponentBaseStats* GetBaseStatsComponent() const { return BaseStatsComponent; }
	// Return entity's InventoryComponent
	FORCEINLINE class UActorComponentInventory* GetInventoryComponent() const { return InventoryComponent; }
	// Return this entity's player controller, cast as a TheHazardsPlayerController
	FORCEINLINE class ATheHazardsPlayerController* GetTheHazardsPlayerController() const { return Cast<ATheHazardsPlayerController>(GetController()); }
};