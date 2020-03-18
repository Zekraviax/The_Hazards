#include "SubWidget_StatusEffectIcon.h"


// Functions
// --------------------------------------------------

// ------------------------- Widget
void USubWidget_StatusEffectIcon::UpdateStatusEffectData(F_StatusEffect_Base NewStatusEffectData)
{
	StatusEffectData.CurrentStackCount = NewStatusEffectData.CurrentStackCount;
	StatusEffectData.CurrentTime = NewStatusEffectData.CurrentTime;
}