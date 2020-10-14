#include "BaseClass_Widget_PlayerHUD.h"

#include "Entity_Base.h"


void UBaseClass_Widget_PlayerHUD::NativeTick(const FGeometry& MyGeometry, float DeltaTime)
{
	Super::NativeTick(MyGeometry, DeltaTime);

	if (PlayerReference) {
		PlayerHealth_Current = PlayerReference->CurrentStats.HealthPoints;
		PlayerHealth_Maximum = PlayerReference->TotalStats.HealthPoints;

		PlayerAura_Current = PlayerReference->CurrentStats.AuraPoints;
		PlayerAura_Maximum = PlayerReference->TotalStats.AuraPoints;
	}
}