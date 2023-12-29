#pragma once


#include "CoreMinimal.h"

#include "Components/ActorComponent.h"
#include "TheHazardsVariables.h"

#include "ActorComponentInventory.generated.h"


UENUM(BlueprintType)
enum class ECurrentWeaponEquippedSlot : uint8
{
	Primary,
	Secondary,
	Tertiary
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THEHAZARDS_API UActorComponentInventory : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UActorComponentInventory();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/*
	// Armour
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FItemBase EquippedHeadItem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FItemBase EquippedChestItem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FItemBase EquippedGlovesItem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FItemBase EquippedLegsItem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FItemBase EquippedBootsItem;

	// Weapons
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FItemBase EquippedPrimaryWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FItemBase EquippedSecondaryWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FItemBase EquippedTertiaryWeapon;

	// Other
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FItemBase EquippedQuickUseItem;
	*/

	// List of uneqipped items in this character's inventory
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FItemBase> ItemsList;

	// Weapons
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ECurrentWeaponEquippedSlot CurrentEquippedWeaponSlotEnum;

	//void SwapItems(FItemBase ItemOne, FItemBase ItemTwo, FString ItemOneDestination, FString ItemTwoDestination);

	void SetEquippedWeaponSlotEnum(ECurrentWeaponEquippedSlot NewSlotEnum);
	ECurrentWeaponEquippedSlot ReturnEquippedWeaponSlotEnum();
	FItemBase ReturnEquippedWeapon();

	FItemBase ReturnEquippedHeadArmour();
	FItemBase ReturnEquippedTorsoArmour();
	FItemBase ReturnEquippedHandArmour();
	FItemBase ReturnEquippedLegArmour();
	FItemBase ReturnEquippedBootsArmour();
	FItemBase ReturnEquippedPrimaryWeapon();
	FItemBase ReturnEquippedSecondaryWeapon();
	FItemBase ReturnEquippedTertiaryWeapon();
	FItemBase ReturnEquippedQuickUseItem();

	// Armour
	float ReturnTotalDamageMitigation();

	// Easy access to the player's equipped gear and data
	void ReturnEquippedWeaponNormalDamage(float &DamagePerShot) { DamagePerShot = ReturnEquippedPrimaryWeapon().WeaponData.DamagePerShot; }
	void ReturnEquippedWeaponSpecialDamage(float &DamagePerShot) { DamagePerShot = ReturnEquippedPrimaryWeapon().WeaponData.SpecialAttackDamagePerShot; }
};