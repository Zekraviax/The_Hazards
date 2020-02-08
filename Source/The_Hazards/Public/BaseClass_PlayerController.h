// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BaseClass_PlayerController.generated.h"


UCLASS()
class THE_HAZARDS_API ABaseClass_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ABaseClass_PlayerController();

protected:
	virtual void SetupInputComponent() override;

public:

};
