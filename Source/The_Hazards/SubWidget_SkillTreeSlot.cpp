// Fill out your copyright notice in the Description page of Project Settings.


#include "SubWidget_SkillTreeSlot.h"


void USubWidget_SkillTreeSlot::OnMouseHoverBegin(FVector2D Coordinates)
{
	float PosX;
	float PosY;
	int32 ViewportSizeX;
	int32 ViewportSizeY;
	float ViewportScaledValueX;
	float ViewportScaledValueY;

	Description_Reference = CreateWidget<UBaseClass_Widget_OnHoverDescription>(GetWorld(), Description_Class);
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetViewportSize(ViewportSizeX, ViewportSizeY);

	ViewportScaledValueX = (1920 / ViewportSizeX);
	ViewportScaledValueY = (1080 / ViewportSizeY);

	//if (SlotType == E_InventorySlot_SlotType::E_EquipmentSlot) {
	PosX = (Coordinates.X * ViewportScaledValueX) - 505;
	PosY = (Coordinates.Y * ViewportScaledValueY) + 55;
	//}
	//else if (SlotType == E_InventorySlot_SlotType::E_StandardSlot) {
	//	PosX = (Coordinates.X * ViewportScaledValueX) - 555;
	//	PosY = (Coordinates.Y * ViewportScaledValueY) + 5;
	//}

	if (PosY > 405)
		PosY = 405;

	if (Description_Class) {
		Description_Reference->SetPositionInViewport(FVector2D(PosX + 0.f, PosY + 0.f), false);
		Description_Reference->SkillReference = SkillReference;
		Description_Reference->SetText(E_Description_Supertypes::E_Skill);
		Description_Reference->AddToViewport();
	}
	else {
		Description_Reference->RemoveFromParent();
		Description_Reference = NULL;
	}
}

void USubWidget_SkillTreeSlot::OnMouseHoverEnd()
{
	if (Description_Reference) {
		Description_Reference->RemoveFromParent();
		Description_Reference = NULL;
	}
}