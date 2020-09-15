#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

#include "SubWidget_WarningAndErrorPrompt.generated.h"

// Exclusive enums
UENUM(BlueprintType)
enum class E_WarningAndError_Types : uint8
{
	E_OverwriteSaveFile,
	E_DoubleCheckLoadGame,
	E_UnsavedKeybinds
};

UENUM(BlueprintType)
enum class E_WarningAndError_ConfirmButtonFunctions : uint8
{
	E_OverwriteSaveFile,
	E_LoadGame,
	E_SaveKeybindsAndClose,
};

UENUM(BlueprintType)
enum class E_WarningAndError_DenyButtonFunctions : uint8
{
	E_ClosePromptWidget,
	E_CancelKeybindWarning
};


UCLASS()
class THE_HAZARDS_API USubWidget_WarningAndErrorPrompt : public UUserWidget
{
	GENERATED_BODY()
	
public:
// Base Variables
// --------------------------------------------------

// ------------------------- Components
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	UTextBlock* HeaderText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	UTextBlock* BodyText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	UTextBlock* DenyButtonText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	UTextBlock* ConfirmButtonText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	UButton* DenyButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components", meta = (BindWidget))
	UButton* ConfirmButton;

// ------------------------- References
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "References")
	UUserWidget* ParentWidget_Reference;

// ------------------------- Prompt
	UPROPERTY()
	E_WarningAndError_ConfirmButtonFunctions ConfirmFunctionEnum;

	UPROPERTY()
	E_WarningAndError_DenyButtonFunctions DenyFunctionEnum;

// Functions
// --------------------------------------------------

// ------------------------- Prompt
	UFUNCTION()
	void SetPromptText(E_WarningAndError_Types PromptType);

	UFUNCTION(BlueprintCallable)
	void ConfirmButtonSwitchFunction();

	UFUNCTION(BlueprintCallable)
	void DenyButtonSwitchFunction();
};