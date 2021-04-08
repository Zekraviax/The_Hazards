#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "SpecialAttackActor_Base.h"
#include "TheHazards_GameMode.h"

#include "FunctionLibrary_SpecialAttacks.generated.h"

#define SPECIAL_ATTACK_COUNT_TOTAL 4

// Forward Declarations
class AEntity_Base;


UCLASS()
class THE_HAZARDS_API AFunctionLibrary_SpecialAttacks : public AActor
{
	GENERATED_BODY()
	
public:	
// Base Variables
// --------------------------------------------------

// ------------------------- Entity
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	AEntity_Base* LinkedEntity;

// ------------------------- Special Attack Actors
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ASpecialAttackActor_Base> Assassinate_Class;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<ASpecialAttackActor_Base> DownwardStrike_Class;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//FActorSpawnParameters SpawnInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ASpecialAttackActor_Base* SpecialAttackActor_Reference;



// Functions
// --------------------------------------------------

// ------------------------- Function Pointers
	// The Function Pointer Variable Type. Functions take in 0 parameters and return void
	typedef void (AFunctionLibrary_SpecialAttacks::*FunctionPtrType)(void);

	// A static array of Function Pointers
	FunctionPtrType SpecialAttackFunctions[SPECIAL_ATTACK_COUNT_TOTAL];

	// Call a special attack function from the Function Pointer Array. Implementation does not vary in subclasses, so not virtual
	void CallSpecialAttackFunction(E_Weapon_SpecialAttacks SpecialAttack);

	// Initialize the array
	void InitializeSpecialAttacks();

	//void SpawnSpecialAttackActor(E_Weapon_SpecialAttacks SpecialAttack);

// ------------------------- Special Attacks
	virtual void Assassinate();
	virtual void Downwards_Strike();
	virtual void Parry();
	virtual void Swing_Around();
};
