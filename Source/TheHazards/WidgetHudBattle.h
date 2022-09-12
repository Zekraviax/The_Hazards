#pragma once


#include "CoreMinimal.h"

#include "Components/TextBlock.h"

#include "Blueprint/UserWidget.h"
#include "WidgetHudBattle.generated.h"


UCLASS()
class THEHAZARDS_API UWidgetHudBattle : public UUserWidget
{
	GENERATED_BODY()


public:
	// Text for displaying current and maximum health points
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats, meta = (BindWidget))
	//UTextBlock* HealthPointsText;

	// Text for displaying current and maximum aura points
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats, meta = (BindWidget))
	UTextBlock* AuraPointsText;

	/**
	 * Called only when the text needs to be changed, as opposed to every tick
	 * @param Current	The player entity's current aura points
	 * @param Maximum	The player entity's maximum aura points
	 */
	UFUNCTION()
	void UpdateAuraPointsText(float Current, float Maximum);
};