#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "TheHazards_GameMode.h"
#include "Components/TextBlock.h"

#include "BaseClass_Widget_DialogueBranch.generated.h"

// Forward Declarations
class UBaseClass_Widget_Dialogue;
class AEntity_NPC;


UCLASS()
class THE_HAZARDS_API UBaseClass_Widget_DialogueBranch : public UUserWidget
{
	GENERATED_BODY()
	
public:
// Base Variables
// --------------------------------------------------

	// ------------------------- Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (BindWidget))
	UTextBlock* ButtonLabel;

	// ------------------------- Dialogue
	UPROPERTY()
	F_Dialogue_Branch DialogueBranch;

	UPROPERTY()
	UBaseClass_Widget_Dialogue* DialogueWindowReference;

	UPROPERTY()
	AEntity_NPC* SpeakerReference;

	// Functions
	// --------------------------------------------------
	UFUNCTION(BlueprintCallable)
	void OnButtonPressed();
};
