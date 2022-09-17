#pragma once


#include "CoreMinimal.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

#include "Blueprint/UserWidget.h"
#include "WidgetHudBattle.generated.h"


UCLASS()
class THEHAZARDS_API UWidgetHudBattle : public UUserWidget
{
	GENERATED_BODY()


public:
	// Text for displaying current and maximum health points
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats, meta = (BindWidget))
	UTextBlock* HealthPointsText;

	// Visual representation of current and maximum health points
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats, meta = (BindWidget))
	UProgressBar* HealthPointsProgressBar;

	// Text for displaying current and maximum aura points
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats, meta = (BindWidget))
	UTextBlock* AuraPointsText;

	// Visual representation of current and maximum aura points
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats, meta = (BindWidget))
	UProgressBar* AuraPointsProgressBar;

	/**
	 * Called only when the text needs to be changed, as opposed to every tick
	 * @param Current	The player entity's current health points
	 * @param Maximum	The player entity's maximum health points
	 */
	UFUNCTION()
	void UpdateHealthPointsInHud(float Current, float Maximum);

	/**
	 * Called only when the text needs to be changed, as opposed to every tick
	 * @param Current	The player entity's current aura points
	 * @param Maximum	The player entity's maximum aura points
	 */
	UFUNCTION()
	void UpdateAuraPointsInHud(float Current, float Maximum);
};