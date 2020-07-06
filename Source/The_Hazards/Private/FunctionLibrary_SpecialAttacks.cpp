#include "FunctionLibrary_SpecialAttacks.h"


// Define Special Attack Indices
#define ASSASSINATE 0
#define DOWNWARDS_STRIKE 1
#define PARRY 2
#define SWING_AROUND 3

// Initialize Special Attacks
void AFunctionLibrary_SpecialAttacks::InitializeSpecialAttacks()
{
	SpecialAttackFunctions[ASSASSINATE] = &AFunctionLibrary_SpecialAttacks::Assassinate;
	SpecialAttackFunctions[DOWNWARDS_STRIKE] = &AFunctionLibrary_SpecialAttacks::Downwards_Strike;
	SpecialAttackFunctions[PARRY] = &AFunctionLibrary_SpecialAttacks::Parry;
	SpecialAttackFunctions[SWING_AROUND] = &AFunctionLibrary_SpecialAttacks::Swing_Around;
}

// ------------------------- Dagger
void AFunctionLibrary_SpecialAttacks::Assassinate()
{

}

// ------------------------- Broadsword
void AFunctionLibrary_SpecialAttacks::Downwards_Strike()
{

}

// ------------------------- Rapier
void AFunctionLibrary_SpecialAttacks::Parry()
{

}

// ------------------------- Flail
void AFunctionLibrary_SpecialAttacks::Swing_Around()
{

}

// Call Special Attacks
void AFunctionLibrary_SpecialAttacks::CallSpecialAttackFunction(int32 SkillIndex)
{

}