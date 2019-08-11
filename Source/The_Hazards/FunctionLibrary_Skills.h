// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Engine/DataTable.h"
#include "TheHazards_GameMode.h"

#include "FunctionLibrary_Skills.generated.h"

#define SKILL_COUNT_TOTAL 1

// Forward Declarations
class AEntity_Base;

UCLASS()
class THE_HAZARDS_API AFunctionLibrary_Skills : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	//AFunctionLibrary_Skills();

// Base Variables
// --------------------------------------------------

// ------------------------- Entity
	UPROPERTY()
	AEntity_Base* LinkedEntity;

// ------------------------- Skill Tree DataTable
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable* SkillDataTable_Reference;

// Functions
// --------------------------------------------------

// ------------------------- Function Pointers
	//The Function Pointer Variable Type. Functions take in 0 parameters and return void
	typedef void (AFunctionLibrary_Skills::*FunctionPtrType)(void);

	//A static array of 30 Function Pointers
	FunctionPtrType SkillFunctions[SKILL_COUNT_TOTAL];

	//Call a skill function from the Function Pointer Array. Implementation does not vary in subclasses, so not virtual
	void CallSkillFunction(int32 SkillIndex);

	//Initialize the array
	void InitializeSkills();

// ------------------------- AER Skills
	virtual void AER_Base();
};