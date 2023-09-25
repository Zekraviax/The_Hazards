#pragma once


#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"
#include "Components/Button.h"

#include "WidgetMenuPause.generated.h"


UCLASS()
class THEHAZARDS_API UWidgetMenuPause : public UUserWidget
{
	GENERATED_BODY()

public:
	// Button for opening the multiplayer menu
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* OpenMultiplayerMenuButton;

	// Open the multiplayer menu
	UFUNCTION(BlueprintCallable)
	void OpenMultiplayerMenu();

	UFUNCTION(BlueprintCallable)
	void OpenOptionsMenu();

	UFUNCTION(BlueprintCallable)
	void SaveGame();

	UFUNCTION(BlueprintCallable)
	void LoadGame();

	UFUNCTION(BlueprintCallable)
	void QuitGame();
};
