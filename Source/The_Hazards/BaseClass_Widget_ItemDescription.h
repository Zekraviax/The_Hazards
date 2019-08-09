// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "TheHazards_GameMode.h"
#include "Components/TextBlock.h"

#include "BaseClass_Widget_ItemDescription.generated.h"


UCLASS()
class THE_HAZARDS_API UBaseClass_Widget_ItemDescription : public UUserWidget
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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item")
	F_Item_BaseStruct ItemReference;

// Functions
// --------------------------------------------------
	UFUNCTION(BlueprintCallable)
	void SetText();
};
