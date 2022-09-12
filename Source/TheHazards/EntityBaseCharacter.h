#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EntityBaseCharacter.generated.h"


class UActorComponentBaseStats;
class UInputComponent;
class UWidgetHudBattle;


UCLASS(config=Game)
class AEntityBaseCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* Mesh1P;

	/** Gun mesh: 1st person view (seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* FP_Gun;

	/** Location on gun mesh where projectiles should spawn. */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USceneComponent* FP_MuzzleLocation;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCameraComponent;

	// Entity's statistics
	UPROPERTY(VisibleDefaultsOnly, Category = Gameplay)
	UActorComponentBaseStats* BaseStatsComponent;

public:
	AEntityBaseCharacter();


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

	// Used to position the camera off the ground
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float CharacterHeight = 64.f;

	// Used in changing and reseting the entity's move speed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float BaseMoveSpeed = 600.f;

	// Used to add the widget to the players' screen whenever their character is spawned
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Interface)
	TSubclassOf<UWidgetHudBattle> WidgetHudBattleClass;

	// Keep a reference to the widget itself so we can show and hide it instead of creating and destroying it every time
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Interface)
	UWidgetHudBattle* WidgetHudBattleReference;

	// Used in the tick function to adjust the camera height
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gameplay)
	bool IsCrouching = false;

	// Used in the tick function to drain Aura Points
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Gameplay)
	bool IsSprinting = false;


protected:
	/** Fires a projectile. */
	void OnFire();

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

	
protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** Returns Mesh1P subobject **/
	FORCEINLINE class USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }
	// Return entity's BaseStatsComponent
	FORCEINLINE class UActorComponentBaseStats* GetBaseStatsComponent() const { return BaseStatsComponent; }

	// Used for crouching in the Tick() function
	float LerpValue;

	// Used for values that are adjusted over time in the Tick() function,
	// such as crouch height and HP/AP regeneration per tick
	float LerpRate = 0.05f;
};