// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FunctionLibrary_SpecialAttacks.generated.h"

UCLASS()
class THE_HAZARDS_API AFunctionLibrary_SpecialAttacks : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFunctionLibrary_SpecialAttacks();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
