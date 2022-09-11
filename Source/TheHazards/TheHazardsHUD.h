// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TheHazardsHUD.generated.h"

UCLASS()
class ATheHazardsHUD : public AHUD
{
	GENERATED_BODY()

public:
	ATheHazardsHUD();

	// Crosshair location is used for linetracing weapon fire
	FVector2D CrosshairPosition;

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

