#pragma once


#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"

#include "WidgetMenuHostSession.generated.h"


UCLASS()
class THEHAZARDS_API UWidgetMenuHostSession : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// Used to begin hosting a session
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* LaunchSessionButton;

	// Begin hosting a session and take the player to the 'lobby' menu
	UFUNCTION(BlueprintCallable)
	void LaunchSession();
};
