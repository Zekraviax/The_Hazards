// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "TheHazards_GameMode.h"
#include "Components/ComboBoxString.h"
#include "Components/EditableText.h"

#include "BaseClass_Widget_CharCreator.generated.h"

// Forward Declarations
class AEntity_Base;


UCLASS()
class THE_HAZARDS_API UBaseClass_Widget_CharCreator : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// Base Variables
	// --------------------------------------------------

	// ------------------------- Player-related variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variables")
	AEntity_Base* PlayerReference;

	// ------------------------- Components
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	UEditableText* Name_TextBox;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	UComboBoxString* Race_DropDown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	UComboBoxString* Element_DropDown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	UComboBoxString* Faction_DropDown;

	// Functions
	// --------------------------------------------------
	UFUNCTION(BlueprintCallable)
	void FinalizeCharacter();
};