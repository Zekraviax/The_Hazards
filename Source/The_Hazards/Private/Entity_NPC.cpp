#include "Entity_NPC.h"

#include "Entity_Player.h"
#include "BaseClass_PlayerController.h"


AEntity_NPC::AEntity_NPC()
{
	InteractBox = CreateDefaultSubobject<UBoxComponent>("InteractBox");
	InteractBox->SetupAttachment(RootComponent);

	CurrentDialogueIndex = -1;
}


// Called when the game starts or when spawned
void AEntity_NPC::BeginPlay()
{
	Super::BeginPlay();

	// Setup InteractBox collisions
	InteractBox->SetCollisionProfileName(TEXT("Trigger"));
	InteractBox->SetGenerateOverlapEvents(true);
	OnActorEndOverlap.AddDynamic(this, &AEntity_NPC::OnPlayerEndOverlap);
}


void AEntity_NPC::OnPlayerEndOverlap(class AActor* Self, class AActor* OtherActor)
{
	if (DialogueWidget_Instance) {
		DialogueWidget_Instance->RemoveFromParent();
		DialogueWidget_Instance = NULL;
	}
}


void AEntity_NPC::PlayerInteract(AEntity_Player* PlayerReference)
{
	// Prevent the player from attacking while speaking
	if (PlayerReference->CanAttack)
		PlayerReference->CanAttack = false;

	if (!DialogueWidget_Instance && DialogueWidget_Class) {
		DialogueWidget_Instance = CreateWidget<UBaseClass_Widget_Dialogue>(GetWorld(), DialogueWidget_Class);

		DialogueWidget_Instance->CurrentDialogueLine = DialogueLines[0];
		DialogueWidget_Instance->UpdateDialogueWidget();
		CurrentDialogueIndex = 0;

		DialogueWidget_Instance->AddToViewport();
	}
	// Open Branching Dialogue Widget
	else if (DialogueWidget_Instance && DialogueBranchWidget_Class && DialogueLines[CurrentDialogueIndex].NextActionInConversation == E_Conversation_NextActionInConversation::E_OpenDialogueBranch) {
		DialogueWidget_Instance->DialogueOptions_ScrollBox->SetVisibility(ESlateVisibility::Visible);
		DialogueWidget_Instance->BackgroundFade->SetVisibility(ESlateVisibility::Visible);

		for (int i = 0; i < DialogueLines[CurrentDialogueIndex].DialogueBranchOptions.Num(); i++) {
			DialogueBranchWidget_Instance = CreateWidget<UBaseClass_Widget_DialogueBranch>(GetWorld(), DialogueBranchWidget_Class);
			DialogueBranchWidget_Instance->DialogueBranch = DialogueLines[CurrentDialogueIndex].DialogueBranchOptions[i];
			DialogueBranchWidget_Instance->ButtonLabel->SetText(FText::FromString(DialogueBranchWidget_Instance->DialogueBranch.DialogueLine));

			DialogueBranchWidget_Instance->SpeakerReference = this;
			DialogueBranchWidget_Instance->DialogueWindowReference = DialogueWidget_Instance;

			DialogueWidget_Instance->DialogueOptions_ScrollBox->AddChild(DialogueBranchWidget_Instance);
		}
	}
	// Open Shop Widget
	else if (!ItemShop_Instance && ItemShop_Class && DialogueLines[CurrentDialogueIndex].NextActionInConversation == E_Conversation_NextActionInConversation::E_OpenShop) {
		ItemShop_Instance = CreateWidget<UBaseClass_Widget_ItemShop>(GetWorld(), ItemShop_Class);
		ItemShop_Instance->ShopkeeperReference = this;
		ItemShop_Instance->PopulateShop();

		ItemShop_Instance->AddToViewport();
	}
	// Next Line in Conversation
	else if (DialogueWidget_Instance && DialogueLines.IsValidIndex(DialogueLines[CurrentDialogueIndex].NextLineIndex) && DialogueLines[CurrentDialogueIndex].NextActionInConversation == E_Conversation_NextActionInConversation::E_OpenDialogueBranch) {
		CurrentDialogueIndex = DialogueLines[CurrentDialogueIndex].NextLineIndex;

		DialogueWidget_Instance->CurrentDialogueLine = DialogueLines[CurrentDialogueIndex];
		DialogueWidget_Instance->UpdateDialogueWidget();
	}
	// End of Conversation
	else if (DialogueWidget_Instance && DialogueLines[CurrentDialogueIndex].NextLineIndex == -1 || !DialogueWidget_Instance || DialogueLines[CurrentDialogueIndex].NextActionInConversation == E_Conversation_NextActionInConversation::E_CloseDialogue) {
		if (DialogueWidget_Instance)
			DialogueWidget_Instance->RemoveFromParent();

		DialogueWidget_Instance = NULL;
		CurrentDialogueIndex = -1;

		PlayerReference->CanAttack = true;
	}
}