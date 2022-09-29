#pragma once


#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/EditableText.h"

#include "WidgetMenuDeveloper.generated.h"


class AEntityPlayerCharacter;


UCLASS()
class THEHAZARDS_API UWidgetMenuDeveloper : public UUserWidget
{
	// Menu with commands for testing the game
	GENERATED_BODY()
	
public:
	// Reference to the player's entity for easy access
	UPROPERTY()
	AEntityPlayerCharacter* PlayerCharacter;

	// Get current values and fill them in to the editable text boxwidget
	UFUNCTION()
	void PopulateEditableTextBoxes();

	// // // Functions that interact with the player character

	// // Edit health and aura

	// Edit current health
	// Function should only fire if the number chosen is valid
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* EditCurrentHealthButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UEditableText* EditCurrentHealthTextBox;

	UFUNCTION(BlueprintCallable)
	void EditCurrentHealth();

	// Edit maximum health
	// Function should only fire if the number chosen is valid
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* EditMaximumHealthButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UEditableText* EditMaximumHealthTextBox;

	UFUNCTION(BlueprintCallable)
	void EditMaximumHealth();

	// Edit current aura
	// Function should only fire if the number chosen is valid
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* EditCurrentAuraButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UEditableText* EditCurrentAuraTextBox;

	UFUNCTION(BlueprintCallable)
	void EditCurrentAura();

	// Edit maximum aura
	// Function should only fire if the number chosen is valid
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* EditMaximumAuraButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UEditableText* EditMaximumAuraTextBox;

	UFUNCTION(BlueprintCallable)
	void EditMaximumAura();
};
