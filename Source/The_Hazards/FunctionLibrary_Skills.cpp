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

	MoveSpeedBonusPercentage = MoveSpeedBonusPercentage;

	LinkedEntity->SkillStats.SecondaryStats.MoveSpeed_Multiplier += (MoveSpeedBonusPercentage);
}

// Call skills
void AFunctionLibrary_Skills::CallSkillFunction(int32 SkillIndex)
{
	if (SkillIndex != 101)
		return;

	(this->* (SkillFunctions[SkillIndex]))();
}