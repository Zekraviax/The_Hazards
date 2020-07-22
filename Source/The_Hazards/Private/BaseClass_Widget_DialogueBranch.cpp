#include "BaseClass_Widget_DialogueBranch.h"

#include "BaseClass_Widget_Dialogue.h"
#include "Entity_NPC.h"


void UBaseClass_Widget_DialogueBranch::OnButtonPressed()
{
	SpeakerReference->CurrentDialogueIndex = DialogueBranch.NextLineIndex;
	DialogueWindowReference->CurrentDialogueLine = SpeakerReference->DialogueLines[DialogueBranch.NextLineIndex];
	DialogueWindowReference->ClearDialogueBranches();
	DialogueWindowReference->UpdateDialogueWidget();
}