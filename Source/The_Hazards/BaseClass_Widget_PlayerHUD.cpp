// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseClass_Widget_PlayerHUD.h"

#include "Entity_Base.h"

void UBaseClass_Widget_PlayerHUD::NativeTick(const FGeometry& MyGeometry, float DeltaTime)
{
	Super::NativeTick(MyGeometry, DeltaTime);

	if (PlayerReference) {
		PlayerHealth_Current = PlayerReference->BaseStats_Current.HealthPoints;
		PlayerHealth_Maximum = PlayerReference->BaseStats_Total.HealthPoints;

		PlayerAura_Current = PlayerReference->BaseStats_Current.AuraPoints;
		PlayerAura_Maximum = PlayerReference->BaseStats_Total.AuraPoints;
	}

}