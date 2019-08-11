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

// ------------------------- Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (BindWidget))
	UImage* BackgroundImage;

// ------------------------- Bound variables
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bound Variables")
	AEntity_Base* PlayerReference;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bound Variables")
	int32 SkillPoints_Bind;
};
