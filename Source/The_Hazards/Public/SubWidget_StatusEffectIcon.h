// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/ProgressBar.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "TheHazards_GameMode.h"

#include "SubWidget_StatusEffectIcon.generated.h"


UCLASS()
class THE_HAZARDS_API USubWidget_StatusEffectIcon : public UUserWidget
{
	GENERATED_BODY()

public:

// Base Variables
// --------------------------------------------------

// ------------------------- Status Effect
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	F_StatusEffect_Base StatusEffectData;

// ------------------------- Components
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	UImage* StatusEffectIcon;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	UProgressBar* TimerBar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	UTextBlock* StackCountText;

// ------------------------- Timer Handle
	//UPROPERTY()
	//FTimerHandle StatusEffectTickTimerHandle;

// Functions
// --------------------------------------------------

// ------------------------- Widget
	UFUNCTION()
	void UpdateStatusEffectData(F_StatusEffect_Base NewStatusEffectData);
};
