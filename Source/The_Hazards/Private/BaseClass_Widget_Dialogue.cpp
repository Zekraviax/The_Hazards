#include "BaseClass_Widget_Dialogue.h"

#include "Entity_NPC.h"


//void UBaseClass_Widget_Dialogue::SwitchFunctionOnIndex(int32 NewIndex)
//{
//
//}


void UBaseClass_Widget_Dialogue::UpdateDialogueWidget()
{
	DialogueLine->SetText(FText::FromString(CurrentDialogueLine.DialogueLine));
	SpeakerName->SetText(FText::FromString(CurrentDialogueLine.SpeakerName));
	SpeakerImage->SetBrushFromTexture(CurrentDialogueLine.SpeakerImage, true);
}


void UBaseClass_Widget_Dialogue::ClearDialogueBranches()
{
	DialogueOptions_ScrollBox->ClearChildren();
	DialogueOptions_ScrollBox->SetVisibility(ESlateVisibility::Collapsed);
	BackgroundFade->SetVisibility(ESlateVisibility::Collapsed);
}


//void UBaseClass_Widget_Dialogue::OpenShop()
//{
//
//}