// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "TheHazards_GameMode.h"
#include "Components/TextBlock.h"

#include "BaseClass_Widget_CharacterSheet.generated.h"

// Forward Declaration
class AEntity_Base;

UCLASS()
class THE_HAZARDS_API UBaseClass_Widget_CharacterSheet : public UUserWidget
{
	GENERATED_BODY()

public:
	// Variables
	// --------------------------------------------------

	// ------------------------- Player-related variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
	AEntity_Base* PlayerReference;

	// ------------------------- Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (BindWidget))
	UTextBlock* Name_Text;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (BindWidget))
	UTextBlock* Race_Text;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (BindWidget))
	UTextBlock* Element_Text;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (BindWidget))
	UTextBlock* Faction_Text;

	// Functions
	// --------------------------------------------------
	UFUNCTION(BlueprintCallable)
	void OpenCharacterSheet();
};
