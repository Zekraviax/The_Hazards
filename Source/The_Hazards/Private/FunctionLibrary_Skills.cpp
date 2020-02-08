#include "FunctionLibrary_Skills.h"

#include "Entity_Base.h"


// Define Skill Indices
#define AER_BASE 101
#define AQUA_BASE 201
#define IGNIS_BASE 301
#define TERRA_BASE 401
#define VITA_BASE 501


// Initialize indices and skills
void AFunctionLibrary_Skills::InitializeSkills()
{
	SkillFunctions[AER_BASE] = &AFunctionLibrary_Skills::AER_Base;
	SkillFunctions[AQUA_BASE] = &AFunctionLibrary_Skills::AQUA_Base;
	SkillFunctions[IGNIS_BASE] = &AFunctionLibrary_Skills::IGNIS_Base;
	SkillFunctions[TERRA_BASE] = &AFunctionLibrary_Skills::TERRA_Base;
	SkillFunctions[VITA_BASE] = &AFunctionLibrary_Skills::VITA_Base;
}

// ------------------------- Aer Skills
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

// ------------------------- Aqua Skills
void AFunctionLibrary_Skills::AQUA_Base()
{
	float ElementalDefenceBonusPercentage = 0;

	if (LinkedEntity) {
		for (F_Skill_Base &Skill : LinkedEntity->KnownSkills) {
			if (Skill.CurrentLevel > 0) {
				ElementalDefenceBonusPercentage++;
			}
		}
	}

	LinkedEntity->SkillStats.Elemental_Defence += ElementalDefenceBonusPercentage;
}

// ------------------------- Ignis Skills
void AFunctionLibrary_Skills::IGNIS_Base()
{
	float OutgoingDamageBonusPercentage = 0;

	if (LinkedEntity) {
		for (F_Skill_Base &Skill : LinkedEntity->KnownSkills) {
			if (Skill.CurrentLevel > 0) {
				OutgoingDamageBonusPercentage++;
			}
		}
	}

	LinkedEntity->SkillStats.SecondaryStats.OutgoingDamage_Multiplier += OutgoingDamageBonusPercentage;
}

// ------------------------- Terra Skills
void AFunctionLibrary_Skills::TERRA_Base()
{
	float IncomingDamageReductionPercentage = 0;

	if (LinkedEntity) {
		for (F_Skill_Base &Skill : LinkedEntity->KnownSkills) {
			if (Skill.CurrentLevel > 0) {
				IncomingDamageReductionPercentage++;
			}
		}
	}

	LinkedEntity->SkillStats.SecondaryStats.IncomingDamage_Multiplier -= IncomingDamageReductionPercentage;
}

// ------------------------- Vita Skills
void AFunctionLibrary_Skills::VITA_Base()
{
	float HealthRegenerationBonusPercentage = 0;

	if (LinkedEntity) {
		for (F_Skill_Base &Skill : LinkedEntity->KnownSkills) {
			if (Skill.CurrentLevel > 0) {
				HealthRegenerationBonusPercentage++;
			}
		}
	}

	LinkedEntity->SkillStats.HealthPoints_RegenPerSecond += HealthRegenerationBonusPercentage;
}

// Call skills
void AFunctionLibrary_Skills::CallSkillFunction(int32 SkillIndex)
{
	//if (SkillIndex != 101)
	//	return;

	(this->* (SkillFunctions[SkillIndex]))();
}