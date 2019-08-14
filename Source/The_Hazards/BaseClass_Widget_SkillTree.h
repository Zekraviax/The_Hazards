// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/Image.h"
#include "SubWidget_SkillTreeSlot.h"

#include "BaseClass_Widget_SkillTree.generated.h"

// Forward Declarations
class AEntity_Base;

UCLASS()
class THE_HAZARDS_API UBaseClass_Widget_SkillTree : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float DeltaTime) override;

public:
// Base Variables
// --------------------------------------------------

// ------------------------- Player
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Player")
	AEntity_Base* PlayerReference;

// ------------------------- Bound Variables
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bound Variables")
	int32 UnspentSkillPointsBind;

// Functions
// --------------------------------------------------
	UFUNCTION(BlueprintCallable)
	void UpdateAllSkillSlots();
};
