#include "Entity_Player_MainMenu.h"


// Sets default values
AEntity_Player_MainMenu::AEntity_Player_MainMenu()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AEntity_Player_MainMenu::BeginPlay()
{
	Super::BeginPlay();

	if (MainMenu_Class) {
		CurrentOpenMenuWidget = CreateWidget<UBaseClass_Widget_MainMenu>(GetWorld(), MainMenu_Class);
		Cast<UBaseClass_Widget_MainMenu>(CurrentOpenMenuWidget)->PlayerReference = this;
		CurrentOpenMenuWidget->AddToViewport();

		CurrentOpenMenuWidget_Class = MainMenu_Class;
	}
}

// Called every frame
void AEntity_Player_MainMenu::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEntity_Player_MainMenu::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("PauseGame", IE_Released, this, &AEntity_Player_MainMenu::CloseWidget).bExecuteWhenPaused = true;
}


void AEntity_Player_MainMenu::CloseWidget()
{
	CurrentOpenMenuWidget->RemoveFromParent();
	CurrentOpenMenuWidget = NULL;

	// If an Options SubWidget is open, close that widget and option the Options widget
	if (CurrentOpenMenuWidget_Class == AudioMenu_Class ||
		CurrentOpenMenuWidget_Class == GraphicsMenu_Class ||
		CurrentOpenMenuWidget_Class == ControlsMenu_Class ||
		CurrentOpenMenuWidget_Class == KeybindsMenu_Class) {
		
		CurrentOpenMenuWidget_Class = NULL;

		CurrentOpenMenuWidget = CreateWidget<UBaseClass_Widget_Options>(GetWorld(), OptionsMenu_Class);
		Cast<UBaseClass_Widget_Options>(CurrentOpenMenuWidget)->PlayerReference = this;
		CurrentOpenMenuWidget->AddToViewport();
		CurrentOpenMenuWidget_Class = OptionsMenu_Class;
	}
	else {
		CurrentOpenMenuWidget_Class = NULL;
	}
}