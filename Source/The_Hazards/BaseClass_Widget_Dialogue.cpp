// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseClass_Widget_Dialogue.h"

#include "Entity_NPC.h"


void UBaseClass_Widget_Dialogue::UpdateDialogueWidget()
{
	DialogueLine->SetText(FText::FromString(CurrentDialogueLine.DialogueLine));
	SpeakerName->SetText(FText::FromString(CurrentDialogueLine.SpeakerName));
	SpeakerImage->SetBrushFromTexture(CurrentDialogueLine.SpeakerImage, true);
}