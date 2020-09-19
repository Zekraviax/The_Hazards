#include "BaseClass_Widget_MainMenu.h"

#include "Entity_Player_MainMenu.h"
#include "Entity_Player.h"
#include "BaseClass_PlayerController.h"
#include "BaseClass_MainMenuController.h"
#include "GameFramework/PlayerStart.h"
#include "GameFramework/Controller.h"
#include "GameFramework/Actor.h"
#include "Engine/EngineTypes.h"
#include "Engine/World.h"
#include "TimerManager.h"


void UBaseClass_Widget_MainMenu::ResumeGame()
{

}


void UBaseClass_Widget_MainMenu::NewGame()
{
	FTimerHandle TimerHandle;
	FLatentActionInfo LatentActionInfo;
	FActorSpawnParameters ActorSpawnParameters;
	TArray<AActor*> PlayerStartActors, PlayerMainMenuActors;

	ActorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	// Add loading screen to player viewport
	if (LoadScreen_Class) {
		LoadScreen_Widget = CreateWidget<UBaseClass_Widget_LoadScreen>(GetWorld(), LoadScreen_Class);
		LoadScreen_Widget->AddToViewport();
	}

	// Load first level
	UGameplayStatics::LoadStreamLevel(GetWorld(), "TestTwo", true, false, LatentActionInfo);

	RemoveFromParent();

	// Begin Minimum time delay for displaying the loading screen
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UBaseClass_Widget_MainMenu::ClearLoadingScreen, 0.2f);
	//LoadScreen_Widget->BeginDelayedClearFunction();
}


void UBaseClass_Widget_MainMenu::ClearLoadingScreen()
{
	// Spawn Player
	TArray<AActor*> PlayerStartActors;
	FActorSpawnParameters ActorSpawnParameters;

	if (Player_Entity_Class && GetWorld()) {
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), PlayerStartActors);
		for (int i = 0; i < PlayerStartActors.Num(); i++) {
			if (PlayerStartActors.IsValidIndex(i)) {
				ABaseClass_PlayerController* PlayerControllerRef = Cast<ABaseClass_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

				Player_Entity_Reference = GetWorld()->SpawnActor<AEntity_Player>(Player_Entity_Class, PlayerStartActors[i]->GetActorLocation(), PlayerStartActors[i]->GetActorRotation(), ActorSpawnParameters);
				PlayerControllerRef->Possess(Player_Entity_Reference);
				Player_Entity_Reference->LocalPlayerControllerReference = PlayerControllerRef;
				Player_Entity_Reference->ManualBeginPlay();

				break;
			}
		}
	}

	// Clear Loading Screens
	for (TObjectIterator<UBaseClass_Widget_LoadScreen> Itr; Itr; ++Itr) {
		UBaseClass_Widget_LoadScreen* FoundWidget = *Itr;
		
		if (FoundWidget->IsValidLowLevel())
			FoundWidget->RemoveFromParent();
	}
}



void UBaseClass_Widget_MainMenu::OpenLoadGameMenu()
{
	if (SaveLoad_Class && PlayerReference) {
		CurrentOpenMenuWidget = CreateWidget<UBaseClass_Widget_SaveLoad>(GetWorld(), SaveLoad_Class);
		CurrentOpenMenuWidget->AddToViewport();

		PlayerReference->CurrentOpenMenuWidget = CurrentOpenMenuWidget;
		PlayerReference->CurrentOpenMenuWidget_Class = SaveLoad_Class;
	}
}


void UBaseClass_Widget_MainMenu::OpenOptionsMenu()
{
	if (Options_Class && PlayerReference) {
		CurrentOpenMenuWidget = CreateWidget<UBaseClass_Widget_Options>(GetWorld(), Options_Class);
		Cast<UBaseClass_Widget_Options>(CurrentOpenMenuWidget)->PlayerReference = PlayerReference;
		CurrentOpenMenuWidget->AddToViewport();

		PlayerReference->CurrentOpenMenuWidget = CurrentOpenMenuWidget;
		PlayerReference->CurrentOpenMenuWidget_Class = Options_Class;
	}
}


void UBaseClass_Widget_MainMenu::QuitGame()
{
	FWindowsPlatformMisc::RequestExit(false);
}


//void UBaseClass_Widget_MainMenu::OpenSaveLoadMenu(bool SaveMode)
//{
//
//}