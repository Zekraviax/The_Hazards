#pragma once


#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"
#include "Components/Button.h"

#include "WidgetMenuMultiplayer.generated.h"


UCLASS()
class THEHAZARDS_API UWidgetMenuMultiplayer : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// Button for opening the 'Host Session' menu
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* HostSessionMenuButton;

	// Button for opening 'Find Session' menu
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* FindSessionMenuButton;

	// Open the 'Host Session' menu
	UFUNCTION(BlueprintCallable)
	void OpenHostSessionMenu();

	// Open the 'Find Session' menu
	UFUNCTION(BlueprintCallable)
	void OpenFindSessionMenu();
};
