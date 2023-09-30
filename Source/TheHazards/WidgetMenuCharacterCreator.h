#pragma once


#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"
#include "Components/ComboBoxString.h"
#include "Components/EditableText.h"

#include "WidgetMenuCharacterCreator.generated.h"


UCLASS()
class THEHAZARDS_API UWidgetMenuCharacterCreator : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UEditableText* PlayerCharacterName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UComboBoxString* ElementsDropdown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UComboBoxString* RacesDropdown;

	UFUNCTION(BlueprintCallable)
	void PopulateDropdowns();

	UFUNCTION(BlueprintCallable)
	void SavePlayerCharacter();
};