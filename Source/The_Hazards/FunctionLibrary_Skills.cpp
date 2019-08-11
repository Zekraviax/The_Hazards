// Fill out your copyright notice in the Description page of Project Settings.


#include "FunctionLibrary_Skills.h"

#include "Entity_Base.h"

// Define Skill Indices
// AER
#define AER_BASE 101

// Initialize indices and skills
void AFunctionLibrary_Skills::InitializeSkills()
{
	SkillFunctions[AER_BASE] = &AFunctionLibrary_Skills::AER_Base;

	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::White, TEXT("Initialize Skills"));
}

// ------------------------- AER Skills
void AFunctionLibrary_Skills::AER_Base()
{
	float MoveSpeedBonusPercentage = 0;

	if (LinkedEntity) {
		for (F_Skill_Base &Skill : LinkedEntity->KnownSkills) {
			if (Skill.CurrentLevel > 0) {
				MoveSpeedBonusPercentage++;
			}
		}
	}

	MoveSpeedBonusPercentage = MoveSpeedBonusPercentage / 100;

	LinkedEntity->SkillStats.Move_Speed += (MoveSpeedBonusPercentage);
	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::White, TEXT("Aer Base Skill  /  MovesSpeed Bonus Percentage: " + FString::SanitizeFloat(LinkedEntity->SkillStats.Move_Speed)));
	LinkedEntity->CalculateTotalStats();
}

// Call skills
void AFunctionLibrary_Skills::CallSkillFunction(int32 SkillIndex)
{
	if (SkillIndex < 0)
		return;

	(this->* (SkillFunctions[SkillIndex]))();
}