// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseClass_Widget_SkillTree.h"

#include "Entity_Base.h"

void UBaseClass_Widget_SkillTree::NativeTick(const FGeometry& MyGeometry, float DeltaTime)
{
	Super::NativeTick(MyGeometry, DeltaTime);

	// Update bound variables
	SkillPoints_Bind = PlayerReference->UnspentSkillPoints;
}