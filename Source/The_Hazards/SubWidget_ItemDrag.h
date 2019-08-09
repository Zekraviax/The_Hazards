// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "TheHazards_GameMode.h"
#include "Components/Image.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

#include "SubWidget_ItemDrag.generated.h"


UCLASS()
class THE_HAZARDS_API USubWidget_ItemDrag : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float DeltaTime) override;

public:
// Base Variables
// --------------------------------------------------

// ------------------------- Position
	UPROPERTY()
	float MousePosX;

	UPROPERTY()
	float MousePosY;

// Base Variables
// --------------------------------------------------
	UFUNCTION(BlueprintCallable)
	void SetPosition();
};
