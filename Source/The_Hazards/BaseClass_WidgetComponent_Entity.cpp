// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseClass_WidgetComponent_Entity.h"

#include "Entity_Base.h"

void UBaseClass_WidgetComponent_Entity::NativeConstruct()
{
	Super::NativeConstruct();
}

void UBaseClass_WidgetComponent_Entity::NativeTick(const FGeometry& MyGeometry, float DeltaTime)
{
	Super::NativeTick(MyGeometry, DeltaTime);

	if (LinkedEntity) {
		float PercentValue = FMath::FInterpTo(HealthBar->Percent, (LinkedEntity->BaseStats_Current.HealthPoints / 100), DeltaTime, 5.f);
		HealthBar->SetPercent(PercentValue);
		//HealthBar->Percent = FMath::FInterpTo(HealthBar->Percent, (LinkedEntity->BaseStats_Current.HealthPoints / 100), DeltaTime, 5.f);
		//GEngine->AddOnScreenDebugMessage(-1, 0.05f, FColor::Red, TEXT("Percent Value: " + FString::SanitizeFloat(HealthBar->Percent)));
	}
}