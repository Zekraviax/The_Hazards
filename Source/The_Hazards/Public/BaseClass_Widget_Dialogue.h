// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "TheHazards_GameMode.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "BaseClass_Widget_DialogueBranch.h"
#include "BaseClass_Widget_ItemShop.h"

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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (BindWidget))
	UImage* BackgroundImage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (BindWidget))
	UImage* SpeakerImage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (BindWidget))
	UTextBlock* DialogueLine;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (BindWidget))
	UTextBlock* SpeakerName;

// ------------------------- Widgets
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<class UBaseClass_Widget_DialogueBranch> DialogueBranchWidget_Class;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widgets")
	UBaseClass_Widget_DialogueBranch* DialogueBranchWidget_Reference;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<class UBaseClass_Widget_ItemShop> ItemShopWidget_Class;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widgets")
	UBaseClass_Widget_ItemShop* ItemShopWidget_Reference;

// ------------------------- Dialogue
	UPROPERTY()
	F_Dialogue_Entry CurrentDialogueLine;

	UPROPERTY()
	int32 CurrentDialogueIndex;


// Functions
// --------------------------------------------------
	UFUNCTION()
	void UpdateDialogueWidget();

	UFUNCTION()
	void OpenDialogueBranch();

	UFUNCTION()
	void OpenShop();

	UFUNCTION()
	void SwitchFunctionOnIndex(int32 NewIndex);
};
