#include "BaseClass_Widget_LoadScreen.h"

#include "Engine.h" 
#include "Engine/World.h"
#include "TimerManager.h"


void UBaseClass_Widget_LoadScreen::BeginDelayedClearFunction()
{
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UBaseClass_Widget_LoadScreen::ExecuteDelayedClearFunction, 0.2f);
}


void UBaseClass_Widget_LoadScreen::ExecuteDelayedClearFunction()
{
	RemoveFromParent();
}