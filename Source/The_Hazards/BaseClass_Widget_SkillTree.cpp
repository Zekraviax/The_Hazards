// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseClass_Widget_SkillTree.h"

#include "Entity_Base.h"


void UBaseClass_Widget_SkillTree::NativeTick(const FGeometry& MyGeometry, float DeltaTime)
{
	Super::NativeTick(MyGeometry, DeltaTime);

	// Update bound variables
	UnspentSkillPointsBind = PlayerReference->UnspentSkillPoints;
}

void UBaseClass_Widget_SkillTree::UpdateAllSkillSlots()
{
	WidgetTree->ForEachWidget([&](UWidget* Widget) {
		check(Widget);
		if (Widget->IsA(USubWidget_SkillTreeSlot::StaticClass())) {
			USubWidget_SkillTreeSlot* FoundSlot = Cast<USubWidget_SkillTreeSlot>(Widget);

			if (FoundSlot) {
				for (int i = 0; i < PlayerReference->KnownSkills.Num(); i++) {
					if (PlayerReference->KnownSkills[i].SlotNumber == FoundSlot->SlotNumber) {
						FoundSlot->SkillReference = PlayerReference->KnownSkills[i];
						FoundSlot->SkillImage->SetBrushFromTexture(PlayerReference->KnownSkills[i].SkillImage, true);
					}
				}
			}
		}
	});
}