#include "Entity_Destructible.h"


// ------------------------- Base actor functions
AEntity_Destructible::AEntity_Destructible()
{

}

void AEntity_Destructible::BeginPlay()
{
	// Override Entity_Base stats
	CurrentStats.HealthPoints = 1;
	CurrentStats.HealthPoints_RegenPerSecond = 0;
	TotalStats.HealthPoints = 1;
}