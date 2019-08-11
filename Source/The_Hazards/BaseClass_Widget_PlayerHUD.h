// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Runtime/UMG/Public/Components/ProgressBar.h"

#include "BaseClass_Widget_PlayerHUD.generated.h"

// Forward Declarations
class AEntity_Base;

UCLASS()
class THE_HAZARDS_API UBaseClass_Widget_PlayerHUD : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float DeltaTime) override;

public:

// ------------------------- Bound Variables 
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bound Variables")
	float PlayerHealth_Current;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bound Variables")
	float PlayerHealth_Maximum;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bound Variables")
	float PlayerAura_Current;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bound Variables")
	float PlayerAura_Maximum;

// ------------------------- Player-Related variables
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player")
	AEntity_Base* PlayerReference;
};
