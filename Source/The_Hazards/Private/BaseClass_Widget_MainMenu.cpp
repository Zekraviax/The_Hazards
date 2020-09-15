#include "BaseClass_Widget_MainMenu.h"

#include "Entity_Player_MainMenu.h"
#include "Entity_Player.h"
#include "BaseClass_PlayerController.h"
#include "BaseClass_MainMenuController.h"
#include "GameFramework/PlayerStart.h"
#include "GameFramework/Controller.h"


// Constructor
UBaseClass_Widget_MainMenu::UBaseClass_Widget_MainMenu(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	//Blueprint'/Game/Blueprints/Entity_Player_Blueprint.Entity_Player_Blueprint'
	//static ConstructorHelpers::FObjectFinder<UClass> EntityPlayerBlueprintReference(TEXT("Blueprint'/Game/Blueprints/Entity_Player_Blueprint.Entity_Player_Blueprint_C'"));
	//if (EntityPlayerBlueprintReference.Object != NULL) {
	//	Player_Entity_Class = EntityPlayerBlueprintReference.Object;
	//}
}



void UBaseClass_Widget_MainMenu::ResumeGame()
{

}


void UBaseClass_Widget_MainMenu::NewGame(TSubclassOf<AEntity_Player> EntityPlayerBlueprintClass)
{
	FLatentActionInfo LatentActionInfo;
	FActorSpawnParameters ActorSpawnParameters;
	UWorld* WorldReference = GetWorld();
	TArray<AActor*> PlayerStartActors, PlayerMainMenuActors;

	ActorSpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	// Add loadscreen to player screen
	if (LoadScreen_Class) {
		CurrentOpenMenuWidget = CreateWidget<UBaseClass_Widget_LoadScreen>(WorldReference, LoadScreen_Class);
		CurrentOpenMenuWidget->AddToViewport();
	}

	RemoveFromViewport();

	// Load first level
	UGameplayStatics::LoadStreamLevel(GetWorld(), "TestTwo", true, false, LatentActionInfo);

	// Spawn player
	if (EntityPlayerBlueprintClass) {
		//UGameplayStatics::GetAllActorsOfClass(WorldReference, APlayerStart::StaticClass(), PlayerStartActors);
		//if (PlayerStartActors.IsValidIndex(0)) {
		//	Player_Entity_Reference = WorldReference->SpawnActor<AEntity_Player>(EntityPlayerBlueprintClass, PlayerStartActors[0]->GetActorLocation(), PlayerStartActors[0]->GetActorRotation(), ActorSpawnParameters);
		//}
	}

	// Set up player actor
	//UGameplayStatics::GetGameMode(WorldReference)->SwapPlayerControllers(Cast<APlayerController>(UGameplayStatics::GetPlayerController(WorldReference, 0)), Cast<APlayerController>(PlayerController_Standard_Reference));
	//Player_Entity_Reference->LocalPlayerControllerReference = Cast<ABaseClass_PlayerController>(UGameplayStatics::GetPlayerController(WorldReference, 0));
	//Player_Entity_Reference->LocalPlayerControllerReference->Possess(Player_Entity_Reference);

	// Destroy main menu player actors
	//UGameplayStatics::GetAllActorsOfClass(WorldReference, AEntity_Player_MainMenu::StaticClass(), PlayerMainMenuActors);
	//for (int i = 0; i < PlayerMainMenuActors.Num(); i++) {
	//	PlayerMainMenuActors[i]->Destroy();
	//}

	// Unload main menu level
	//UGameplayStatics::UnloadStreamLevel(WorldReference, "MainMenu", LatentActionInfo, false);

	// Remove widgets
	CurrentOpenMenuWidget->RemoveFromViewport();

	// Call Player BeginPlay
	//Player_Entity_Reference->ManualBeginPlay();
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