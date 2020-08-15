#pragma once

#include "CoreMinimal.h"
#include "Entity_Player.h"

#include "Entity_Player_MainMenu.generated.h"


UCLASS()
class THE_HAZARDS_API AEntity_Player_MainMenu : public AEntity_Player
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEntity_Player_MainMenu();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

// Base Variables
// --------------------------------------------------

// ------------------------- Widgets
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	//TSubclassOf<UBaseClass_Widget_MainMenu> MainMenu_Class;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	//TSubclassOf<UBaseClass_Widget_SaveLoad> SaveLoad_Class;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	//TSubclassOf<UBaseClass_Widget_Options> Options_Class;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	//TSubclassOf<USubwidget_AudioMenu> AudioMenu_Class;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	//TSubclassOf<USubWidget_GraphicsMenu> GraphicsMenu_Class;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	//TSubclassOf<USubWidget_ControlsMenu> ControlsMenu_Class;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	//TSubclassOf<USubWidget_KeybindsMenu> KeybindsMenu_Class;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widgets")
	//TSubclassOf<UUserWidget> CurrentOpenMenuWidget_Class;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widgets")
	//UUserWidget* CurrentOpenMenuWidget_Reference;

// Functions
// --------------------------------------------------

// ------------------------- Widgets
	UFUNCTION()
	void CloseWidget();
};
