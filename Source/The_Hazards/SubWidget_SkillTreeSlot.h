// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/Image.h"

#include "SubWidget_SkillTreeSlot.generated.h"


UCLASS()
class THE_HAZARDS_API USubWidget_SkillTreeSlot : public UUserWidget
{
	GENERATED_BODY()

public:
// Base Variables
// --------------------------------------------------

// ------------------------- Bound Widget Components
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UImage* SkillImage;

// ------------------------- Slot
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 SlotNumber;
};
