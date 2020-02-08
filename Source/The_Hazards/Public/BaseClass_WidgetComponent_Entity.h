// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/ProgressBar.h"
#include "Components/PanelWidget.h"
#include "Components/CanvasPanel.h"
#include "Runtime/UMG/Public/Blueprint/WidgetTree.h"
#include "Runtime/Core/Public/Math/UnrealMathUtility.h"

#include "BaseClass_WidgetComponent_Entity.generated.h"

//Forward Declarations
class AEntity_Base;

UCLASS()
class THE_HAZARDS_API UBaseClass_WidgetComponent_Entity : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float DeltaTime) override;

public:
// Base Variables
// --------------------------------------------------

// ------------------------- Components
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	UProgressBar* HealthBar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	UProgressBar* AuraBar;

// ------------------------- Entity variables
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Entity")
	AEntity_Base* LinkedEntity;
};