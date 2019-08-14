// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Engine/DataTable.h"
#include "TheHazards_GameMode.h"

#include "FunctionLibrary_Skills.generated.h"

// Forward Declarations
class AEntity_Base;

UCLASS()
class THE_HAZARDS_API AFunctionLibrary_Skills : public AActor
{
	GENERATED_BODY()
	
public:	
// Base Variables
// --------------------------------------------------

// ------------------------- Entity
	UPROPERTY()
	AEntity_Base* LinkedEntity;

// ------------------------- Skill Tree DataTable
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable* SkillDataTable_Reference;
};
