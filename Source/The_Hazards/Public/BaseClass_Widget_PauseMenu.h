// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseClass_Widget_PauseMenu.generated.h"

// Forward Declarations
class AEntity_Player;

UCLASS()
class THE_HAZARDS_API UBaseClass_Widget_PauseMenu : public UUserWidget
{
	GENERATED_BODY()

public:
	// Player reference
	UPROPERTY()
	AEntity_Player* LocalPlayerReference;

	// Button Functions
	UFUNCTION(BlueprintCallable)
	void Function_ResumeGame();

	UFUNCTION(BlueprintCallable)
	void Function_QuitToMainMenu();

	UFUNCTION(BlueprintCallable)
	void Function_QuitToDesktop();
};
