#pragma once


#include "CoreMinimal.h"

#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "InterfaceInteractions.h"
#include "Net/UnrealNetwork.h"
#include "TheHazardsPlayerController.h"
#include "TheHazardsVariables.h"

#include "EntityBaseCharacter.generated.h"


class UActorComponentBaseData;
class UActorComponentBaseStats;
class UActorComponentInventory;
class UInputComponent;
class UWidgetHudBattle;


UCLASS(config=Game)
class AEntityBaseCharacter : public ACharacter, public IInterfaceInteractions
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

	// Melee weapon Hitbox
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class UBoxComponent* MeleeWeaponHitbox;

	// Entities must be within this box in order to talk to this NPC
	UPROPERTY(VisibleDefaultsOnly, Category = Gameplay)
	UBoxComponent* InteractBounds;

	// Entity's core data
	UPROPERTY(VisibleDefaultsOnly, Category = Gameplay)
	UActorComponentBaseData* BaseDataComponent;

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
	UPROPERTY()
	FTimerHandle RangedWeaponFireTimerHandle;

	// TimerHandle for a melee weapon's swing
	UPROPERTY()
	FTimerHandle MeleeWeaponSwingTimerHandle;

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

	// Timer for holding the charge
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gameplay)
	FTimerHandle BeginChargeTimerHandle;

	// Timer for the charge duration
	// Charge duration is equal to how long the charge is held
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gameplay)
	FTimerHandle ChargeTimerHandle;

	UPROPERTY()
	bool IsStunned;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gameplay)
	FTimerHandle StunTimerHandle;

	UPROPERTY()
	float MoveForwardValue;
	UPROPERTY()
	float MoveRightValue;

	UPROPERTY()
	bool MoveForwardHeldDown;
	UPROPERTY()
	bool MoveRightHeldDown;

	// Used for crouching in the Tick() function
	UPROPERTY()
	float LerpValue;

	// Used for values that are adjusted over time in the Tick() function,
	// such as crouch height and HP/AP regeneration per tick
	UPROPERTY()
	float LerpRate = 0.05f;

	UFUNCTION()
	void OnCapsuleComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	void BoxComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	UFUNCTION()
	void MeleeWeaponHit(AActor* OtherActor);

	UPROPERTY()
	TArray<AActor*> ActorsToIgnore;

	UPROPERTY()
	TArray<AActor*> MeleeHitboxOverlappingActors;

	// Creating a duplicate CurrentEquippedWeapon variable so we don't have to
	// retrieve it everytime an entity attacks. Instead
	// It will only be retrieved when an entity switches weapons
	// or loads in to the game
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FItemBase CurrentEquippedWeapon;

	UPROPERTY()
	bool IsUsingNormalAttack;

	UPROPERTY()
	bool IsUsingSpecialAttack;

	/** Fires a projectile. */
	UFUNCTION(BlueprintCallable)
	void OnFire();

	// Clear any automatic firing TimerHandles when the fire button is de-pressed
	void OnStopFiring();

	// When a melee weapon animation is finished, set the melee weapon hitbox to not overlap anything anymore
	void OnMeleeWeaponSwingEnd();

	UPROPERTY()
	FTimerHandle SpecialAttackTimerHandle;

	void OnLaunchSpecialAttack();

	void OnSpecialAttackEnd();

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

	void OnStunBegin();
	void OnStunEnd();

	/**
	 * Function called when something hurts this entity
	 * @param Damage	Result of damage formula from attacker
	 * @param Source	Whichever entity is attacking
	 */
	void ReceiveDamage(float Damage, AEntityBaseCharacter* Source);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Dialogue
	UPROPERTY()
	int CurrentDialogueStage = -1;

	virtual bool OnInteract_Implementation() override;

	void ConsumableItemUsed();

	/** Returns Mesh1P subobject **/
	FORCEINLINE class USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }
	// Return entity's components
	FORCEINLINE class UActorComponentBaseData* GetBaseDataComponent() const { return BaseDataComponent; }
	FORCEINLINE class UActorComponentBaseStats* GetBaseStatsComponent() const { return BaseStatsComponent; }
	FORCEINLINE class UActorComponentInventory* GetInventoryComponent() const { return InventoryComponent; }
	// Return this entity's player controller, cast as a TheHazardsPlayerController
	FORCEINLINE class ATheHazardsPlayerController* GetTheHazardsPlayerController() const { return Cast<ATheHazardsPlayerController>(GetController()); }
	// Return this entity's melee weapon hitbox
	FORCEINLINE class UBoxComponent* GetMeleeWeaponHitboxComponent() const { return MeleeWeaponHitbox; }
};