// Fill out your copyright notice in the Description page of Project Settings.


#include "SubWidget_StatusEffectIcon.h"


void USubWidget_StatusEffectIcon::UpdateStatusEffectData(F_StatusEffect_Base NewStatusEffectData)
{
	StatusEffectData.CurrentStackCount = NewStatusEffectData.CurrentStackCount;
	StatusEffectData.CurrentTime = NewStatusEffectData.CurrentTime;

	GEngine->AddOnScreenDebugMessage(-1, 0.3f, FColor::Blue, FString::Printf(TEXT("Current Time: %f"), NewStatusEffectData.CurrentTime));
}