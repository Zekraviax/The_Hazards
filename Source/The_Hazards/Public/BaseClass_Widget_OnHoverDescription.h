// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "TheHazards_GameMode.h"
#include "Components/TextBlock.h"

#include "BaseClass_Widget_OnHoverDescription.generated.h"


UENUM(BlueprintType)
enum class E_Description_Supertypes : uint8
{
	E_Item,
	E_Skill
};

UCLASS()
class THE_HAZARDS_API UBaseClass_Widget_OnHoverDescription : public UUserWidget
{
	GENERATED_BODY()

public:
// Base Variables
// --------------------------------------------------

// ------------------------- Components
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	UTextBlock* Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	UTextBlock* Description;

// ------------------------- Item
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bound Variables")
	F_Item_BaseStruct ItemReference;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Bound Variables")
	F_Skill_Base SkillReference;

// Functions
// --------------------------------------------------
	UFUNCTION(BlueprintCallable)
	void SetText(E_Description_Supertypes Supertype);
};
