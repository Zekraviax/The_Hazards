#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Runtime/Engine/Classes/GameFramework/PlayerInput.h"
#include "Runtime/Engine/Classes/GameFramework/InputSettings.h"
#include "Runtime/CoreUObject/Public/UObject/UObjectGlobals.h"
#include "Components/Image.h"
#include "Components/Button.h"

#include "SubWidget_KeybindsMenu.generated.h"

// Forward Declarations
class AEntity_Player;
class ABaseClass_PlayerController;
class UBaseClass_Widget_Options;
class USubWidget_KeyRebindButton;


UCLASS()
class THE_HAZARDS_API USubWidget_KeybindsMenu : public UUserWidget
{
	GENERATED_BODY()

public:
// Base Variables
// --------------------------------------------------

// ------------------------- Components
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	UImage* BackgroundImage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	UButton* ApplyButton;

// ------------------------- Widgets
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<UBaseClass_Widget_Options> Options_Class;

// ------------------------- References
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "References")
	AEntity_Player* PlayerReference;

// ------------------------- Rebind
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Rebind")
	UInputSettings* InputSettings;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Rebind")
	USubWidget_KeyRebindButton* CurrentSelectedButton;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Rebind")
	FName KeyName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Rebind")
	bool KeyIsAxis;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Rebind")
	bool KeyIsPrimary;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Rebind")
	float KeyAxisScale;

// Functions
// --------------------------------------------------

// ------------------------- Widget
	UFUNCTION(BlueprintCallable)
	void OpenWidget();

	UFUNCTION(BlueprintCallable)
	void CloseWidget();

// ------------------------- Keybinds
	UFUNCTION(BlueprintCallable)
	void RebindAxisKey(FInputAxisKeyMapping AxisKey);

	UFUNCTION(BlueprintCallable)
	void RebindActionKey(FInputActionKeyMapping ActionKey);

	UFUNCTION(BlueprintCallable)
	void CancelRebindKey();

	UFUNCTION(BlueprintCallable)
	void ApplyReboundKeys();
};