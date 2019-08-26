// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "TheHazards_GameMode.h"

#include "BaseClass_Widget_Dialogue.generated.h"

// Forward Declarations
class AEntity_NPC;

UCLASS()
class THE_HAZARDS_API UBaseClass_Widget_Dialogue : public UUserWidget
{
	GENERATED_BODY()

public:
// Base Variables
// --------------------------------------------------

// ------------------------- Components
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	UImage* BackgroundImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	UImage* SpeakerImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	UTextBlock* DialogueLine;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	UTextBlock* SpeakerName;

// ------------------------- Dialogue
	UPROPERTY()
	F_Dialogue_Entry CurrentDialogueLine;


// Functions
// --------------------------------------------------
	UFUNCTION()
	void UpdateDialogueWidget();
};
