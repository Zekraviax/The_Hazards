#include "BaseClass_Widget_DialogueBranch.h"

#include "BaseClass_Widget_Dialogue.h"
#include "Entity_NPC.h"


void UBaseClass_Widget_DialogueBranch::OnButtonPressed()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::FromInt(DialogueBranch.NextLineIndex));

	SpeakerReference->CurrentDialogueIndex = DialogueBranch.NextLineIndex;
	DialogueWindowReference->CurrentDialogueLine = SpeakerReference->DialogueLines[DialogueBranch.NextLineIndex];
	DialogueWindowReference->ClearDialogueBranches();
	DialogueWindowReference->UpdateDialogueWidget();
}