// Fill out your copyright notice in the Description page of Project Settings.


#include "SubWidget_StatBreakdown.h"

#include "Entity_Base.h"


void USubWidget_StatBreakdown::NativeTick(const FGeometry& MyGeometry, float DeltaTime)
{
	Super::NativeTick(MyGeometry, DeltaTime);

	if (PlayerReference) {
		// Level-Up Stats
		LevelupStatsColumn->SetText(FText::FromString("Level-Up Stats: \n\n(" + FString::FromInt(PlayerReference->LevelStats.HealthPoints) + " * " + FString::SanitizeFloat(PlayerReference->LevelStats.SecondaryStats.Maximum_HealthPoints_Multiplier) + ")"
			+ "\n(" + FString::SanitizeFloat(PlayerReference->LevelStats.HealthPoints_RegenPerSecond) + " * " + FString::SanitizeFloat(PlayerReference->LevelStats.SecondaryStats.HealthPoints_Recovery_Multiplier) + ")"
			+ "\n(" + FString::SanitizeFloat(PlayerReference->LevelStats.HealthPoints_RegenStartDelay) + ")"
			+ "\n(" + FString::FromInt(PlayerReference->LevelStats.AuraPoints) + " * " + FString::SanitizeFloat(PlayerReference->LevelStats.SecondaryStats.AuraPoints_Recovery_Multiplier) + ")"
			+ "\n(" + FString::SanitizeFloat(PlayerReference->LevelStats.AuraPoints_RegenPerSecond) + " * " + FString::SanitizeFloat(PlayerReference->LevelStats.SecondaryStats.AuraPoints_Recovery_Multiplier) + ")"
			+ "\n(" + FString::SanitizeFloat(PlayerReference->LevelStats.AuraPoints_RegenStartDelay) + ")"
			+ "\n(" + FString::FromInt(PlayerReference->LevelStats.Physical_Strength) + ")"
			+ "\n(" + FString::FromInt(PlayerReference->LevelStats.Physical_Defence) + " * " + FString::SanitizeFloat(PlayerReference->LevelStats.SecondaryStats.PhysicalDefence_Multiplier) + ")"
			+ "\n(" + FString::FromInt(PlayerReference->LevelStats.Elemental_Strength) + + " * " + FString::SanitizeFloat(PlayerReference->LevelStats.SecondaryStats.SpecialAttack_Multiplier) + ")"
			+ "\n(" + FString::FromInt(PlayerReference->LevelStats.Elemental_Defence) + ")"
			+ "\n(" + FString::FromInt(PlayerReference->LevelStats.Attack_Speed) + " * " + FString::SanitizeFloat(PlayerReference->LevelStats.SecondaryStats.AttackSpeed_Multiplier) + ")"
			+ "\n(" + FString::FromInt(PlayerReference->LevelStats.Move_Speed) + " * " + FString::SanitizeFloat(PlayerReference->LevelStats.SecondaryStats.MoveSpeed_Multiplier) + ")"
			+ "\n(" + FString::FromInt(PlayerReference->LevelStats.Evasiveness) + ")"
			+ "\n(" + FString::FromInt(PlayerReference->LevelStats.Status_Potency) + " * " + FString::SanitizeFloat(PlayerReference->LevelStats.SecondaryStats.StatusPotency_Multiplier) + ")"
			+ "\n(" + FString::FromInt(PlayerReference->LevelStats.Luck) + ")"));

		// Skill Stats
		SkillsStatsColumn->SetText(FText::FromString("Skill Stats: \n\n(" + FString::FromInt(PlayerReference->SkillStats.HealthPoints) + " * " + FString::SanitizeFloat(PlayerReference->SkillStats.SecondaryStats.Maximum_HealthPoints_Multiplier) + ")"
			+ "\n(" + FString::SanitizeFloat(PlayerReference->SkillStats.HealthPoints_RegenPerSecond) + " * " + FString::SanitizeFloat(PlayerReference->SkillStats.SecondaryStats.HealthPoints_Recovery_Multiplier) + ")"
			+ "\n(" + FString::SanitizeFloat(PlayerReference->SkillStats.HealthPoints_RegenStartDelay) + ")"
			+ "\n(" + FString::FromInt(PlayerReference->SkillStats.AuraPoints) + " * " + FString::SanitizeFloat(PlayerReference->SkillStats.SecondaryStats.AuraPoints_Recovery_Multiplier) + ")"
			+ "\n(" + FString::SanitizeFloat(PlayerReference->SkillStats.AuraPoints_RegenPerSecond) + " * " + FString::SanitizeFloat(PlayerReference->SkillStats.SecondaryStats.AuraPoints_Recovery_Multiplier) + ")"
			+ "\n(" + FString::SanitizeFloat(PlayerReference->SkillStats.AuraPoints_RegenStartDelay) + ")"
			+ "\n(" + FString::FromInt(PlayerReference->SkillStats.Physical_Strength) + ")"
			+ "\n(" + FString::FromInt(PlayerReference->SkillStats.Physical_Defence) + " * " + FString::SanitizeFloat(PlayerReference->SkillStats.SecondaryStats.PhysicalDefence_Multiplier) + ")"
			+ "\n(" + FString::FromInt(PlayerReference->SkillStats.Elemental_Strength) + +" * " + FString::SanitizeFloat(PlayerReference->SkillStats.SecondaryStats.SpecialAttack_Multiplier) + ")"
			+ "\n(" + FString::FromInt(PlayerReference->SkillStats.Elemental_Defence) + ")"
			+ "\n(" + FString::FromInt(PlayerReference->SkillStats.Attack_Speed) + " * " + FString::SanitizeFloat(PlayerReference->SkillStats.SecondaryStats.AttackSpeed_Multiplier) + ")"
			+ "\n(" + FString::FromInt(PlayerReference->SkillStats.Move_Speed) + " * " + FString::SanitizeFloat(PlayerReference->SkillStats.SecondaryStats.MoveSpeed_Multiplier) + ")"
			+ "\n(" + FString::FromInt(PlayerReference->SkillStats.Evasiveness) + ")"
			+ "\n(" + FString::FromInt(PlayerReference->SkillStats.Status_Potency) + " * " + FString::SanitizeFloat(PlayerReference->SkillStats.SecondaryStats.StatusPotency_Multiplier) + ")"
			+ "\n(" + FString::FromInt(PlayerReference->SkillStats.Luck) + ")"));

		// Item Stats
		ItemsStatsColumn->SetText(FText::FromString("Item Stats: \n\n(" + FString::FromInt(PlayerReference->ItemStats.HealthPoints) + " * " + FString::SanitizeFloat(PlayerReference->ItemStats.SecondaryStats.Maximum_HealthPoints_Multiplier) + ")"
			+ "\n(" + FString::SanitizeFloat(PlayerReference->ItemStats.HealthPoints_RegenPerSecond) + " * " + FString::SanitizeFloat(PlayerReference->ItemStats.SecondaryStats.HealthPoints_Recovery_Multiplier) + ")"
			+ "\n(" + FString::SanitizeFloat(PlayerReference->ItemStats.HealthPoints_RegenStartDelay) + ")"
			+ "\n(" + FString::FromInt(PlayerReference->ItemStats.AuraPoints) + " * " + FString::SanitizeFloat(PlayerReference->ItemStats.SecondaryStats.AuraPoints_Recovery_Multiplier) + ")"
			+ "\n(" + FString::SanitizeFloat(PlayerReference->ItemStats.AuraPoints_RegenPerSecond) + " * " + FString::SanitizeFloat(PlayerReference->ItemStats.SecondaryStats.AuraPoints_Recovery_Multiplier) + ")"
			+ "\n(" + FString::SanitizeFloat(PlayerReference->ItemStats.AuraPoints_RegenStartDelay) + ")"
			+ "\n(" + FString::FromInt(PlayerReference->ItemStats.Physical_Strength) + ")"
			+ "\n(" + FString::FromInt(PlayerReference->ItemStats.Physical_Defence) + " * " + FString::SanitizeFloat(PlayerReference->ItemStats.SecondaryStats.PhysicalDefence_Multiplier) + ")"
			+ "\n(" + FString::FromInt(PlayerReference->ItemStats.Elemental_Strength) + +" * " + FString::SanitizeFloat(PlayerReference->ItemStats.SecondaryStats.SpecialAttack_Multiplier) + ")"
			+ "\n(" + FString::FromInt(PlayerReference->ItemStats.Elemental_Defence) + ")"
			+ "\n(" + FString::FromInt(PlayerReference->ItemStats.Attack_Speed) + " * " + FString::SanitizeFloat(PlayerReference->ItemStats.SecondaryStats.AttackSpeed_Multiplier) + ")"
			+ "\n(" + FString::FromInt(PlayerReference->ItemStats.Move_Speed) + " * " + FString::SanitizeFloat(PlayerReference->ItemStats.SecondaryStats.MoveSpeed_Multiplier) + ")"
			+ "\n(" + FString::FromInt(PlayerReference->ItemStats.Evasiveness) + ")"
			+ "\n(" + FString::FromInt(PlayerReference->ItemStats.Status_Potency) + " * " + FString::SanitizeFloat(PlayerReference->ItemStats.SecondaryStats.StatusPotency_Multiplier) + ")"
			+ "\n(" + FString::FromInt(PlayerReference->ItemStats.Luck) + ")"));

		// Temporary Stats
		TemporaryStatsColumn->SetText(FText::FromString("Temporary Stats: \n\n(" + FString::FromInt(PlayerReference->TemporaryStats.HealthPoints) + " * " + FString::SanitizeFloat(PlayerReference->TemporaryStats.SecondaryStats.Maximum_HealthPoints_Multiplier) + ")"
			+ "\n(" + FString::SanitizeFloat(PlayerReference->TemporaryStats.HealthPoints_RegenPerSecond) + " * " + FString::SanitizeFloat(PlayerReference->TemporaryStats.SecondaryStats.HealthPoints_Recovery_Multiplier) + ")"
			+ "\n(" + FString::SanitizeFloat(PlayerReference->TemporaryStats.HealthPoints_RegenStartDelay) + ")"
			+ "\n(" + FString::FromInt(PlayerReference->TemporaryStats.AuraPoints) + " * " + FString::SanitizeFloat(PlayerReference->TemporaryStats.SecondaryStats.AuraPoints_Recovery_Multiplier) + ")"
			+ "\n(" + FString::SanitizeFloat(PlayerReference->TemporaryStats.AuraPoints_RegenPerSecond) + " * " + FString::SanitizeFloat(PlayerReference->TemporaryStats.SecondaryStats.AuraPoints_Recovery_Multiplier) + ")"
			+ "\n(" + FString::SanitizeFloat(PlayerReference->TemporaryStats.AuraPoints_RegenStartDelay) + ")"
			+ "\n(" + FString::FromInt(PlayerReference->TemporaryStats.Physical_Strength) + ")"
			+ "\n(" + FString::FromInt(PlayerReference->TemporaryStats.Physical_Defence) + " * " + FString::SanitizeFloat(PlayerReference->TemporaryStats.SecondaryStats.PhysicalDefence_Multiplier) + ")"
			+ "\n(" + FString::FromInt(PlayerReference->TemporaryStats.Elemental_Strength) + +" * " + FString::SanitizeFloat(PlayerReference->TemporaryStats.SecondaryStats.SpecialAttack_Multiplier) + ")"
			+ "\n(" + FString::FromInt(PlayerReference->TemporaryStats.Elemental_Defence) + ")"
			+ "\n(" + FString::FromInt(PlayerReference->TemporaryStats.Attack_Speed) + " * " + FString::SanitizeFloat(PlayerReference->TemporaryStats.SecondaryStats.AttackSpeed_Multiplier) + ")"
			+ "\n(" + FString::FromInt(PlayerReference->TemporaryStats.Move_Speed) + " * " + FString::SanitizeFloat(PlayerReference->TemporaryStats.SecondaryStats.MoveSpeed_Multiplier) + ")"
			+ "\n(" + FString::FromInt(PlayerReference->TemporaryStats.Evasiveness) + ")"
			+ "\n(" + FString::FromInt(PlayerReference->TemporaryStats.Status_Potency) + " * " + FString::SanitizeFloat(PlayerReference->TemporaryStats.SecondaryStats.StatusPotency_Multiplier) + ")"
			+ "\n(" + FString::FromInt(PlayerReference->TemporaryStats.Luck) + ")"));

		// Total Stats
		TotalStatsColumn->SetText(FText::FromString("Total Stats: \n\n" + FString::FromInt(PlayerReference->TotalStats.HealthPoints)
			+ "\n" + FString::SanitizeFloat(PlayerReference->TotalStats.HealthPoints_RegenPerSecond)
			+ "\n" + FString::SanitizeFloat(PlayerReference->TotalStats.HealthPoints_RegenStartDelay)
			+ "\n" + FString::FromInt(PlayerReference->TotalStats.AuraPoints)
			+ "\n" + FString::SanitizeFloat(PlayerReference->TotalStats.AuraPoints_RegenPerSecond)
			+ "\n" + FString::SanitizeFloat(PlayerReference->TotalStats.AuraPoints_RegenStartDelay)
			+ "\n" + FString::FromInt(PlayerReference->TotalStats.Physical_Strength)
			+ "\n" + FString::FromInt(PlayerReference->TotalStats.Physical_Defence)
			+ "\n" + FString::FromInt(PlayerReference->TotalStats.Elemental_Strength)
			+ "\n" + FString::FromInt(PlayerReference->TotalStats.Elemental_Defence)
			+ "\n" + FString::FromInt(PlayerReference->TotalStats.Attack_Speed)
			+ "\n" + FString::FromInt(PlayerReference->TotalStats.Move_Speed)
			+ "\n" + FString::FromInt(PlayerReference->TotalStats.Evasiveness)
			+ "\n" + FString::FromInt(PlayerReference->TotalStats.Status_Potency)
			+ "\n" + FString::FromInt(PlayerReference->TotalStats.Luck)));
	}
}