// Fill out your copyright notice in the Description page of Project Settings.


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
	//InteractBox->OnComponentBeginOverlap.AddDynamic(this, &AEntity_NPC::OnPlayerBeginOverlap);
	OnActorEndOverlap.AddDynamic(this, &AEntity_NPC::OnPlayerEndOverlap);
}


void AEntity_NPC::OnPlayerEndOverlap(class AActor* Self, class AActor* OtherActor)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("PlayerEndOverlap"));
	if (DialogueWidget_Instance) {
		DialogueWidget_Instance->RemoveFromParent();
		DialogueWidget_Instance = NULL;
	}
}


void AEntity_NPC::PlayerInteract()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Player Interact"));

	if (!DialogueWidget_Instance && DialogueWidget_Class) {
		DialogueWidget_Instance = CreateWidget<UBaseClass_Widget_Dialogue>(GetWorld(), DialogueWidget_Class);

		DialogueWidget_Instance->CurrentDialogueLine = DialogueLines[0];
		DialogueWidget_Instance->UpdateDialogueWidget();
		CurrentDialogueIndex = 0;

		DialogueWidget_Instance->AddToViewport();
	}
	else if (DialogueWidget_Instance && DialogueLines[CurrentDialogueIndex].NextLineIndex == -1 || !DialogueWidget_Instance) {
		if (DialogueWidget_Instance)
			DialogueWidget_Instance->RemoveFromParent();

		DialogueWidget_Instance = NULL;

		CurrentDialogueIndex = -1;
	}
	else if (DialogueWidget_Instance && DialogueLines.IsValidIndex(DialogueLines[CurrentDialogueIndex].NextLineIndex)) {
		CurrentDialogueIndex = DialogueLines[CurrentDialogueIndex].NextLineIndex;

		DialogueWidget_Instance->CurrentDialogueLine = DialogueLines[CurrentDialogueIndex];
		DialogueWidget_Instance->UpdateDialogueWidget();

		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Valid Index: " + FString::FromInt(DialogueLines[CurrentDialogueIndex].NextLineIndex)));
	}
}