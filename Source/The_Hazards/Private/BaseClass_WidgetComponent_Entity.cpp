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
		float HealthPercentValue = FMath::FInterpTo(HealthBar->Percent, (LinkedEntity->CurrentStats.HealthPoints / 100), DeltaTime, 5.f);
		float AuraPercentValue = FMath::FInterpTo(AuraBar->Percent, (LinkedEntity->CurrentStats.AuraPoints / 100), DeltaTime, 5.f);
		HealthBar->SetPercent(HealthPercentValue);
		AuraBar->SetPercent(AuraPercentValue);
	}
}