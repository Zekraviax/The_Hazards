#include "TheHazards_GameInstance.h"

#include "SaveFile_Slot.h"
#include "SaveFile_MetaList.h"
#include "BaseClass_Widget_LoadScreen.h"
#include "BaseClass_PlayerController.h"
#include "TheHazards_GameInstance_TActor.h"
#include "Entity_Player.h"
#include "GameFramework/PlayerStart.h"
#include "GameFramework/SaveGame.h"
#include "Delegates/Delegate.h"
#include "Engine/Level.h"


USaveFile_MetaList* UTheHazards_GameInstance::ReturnMetaList()
{
	//USaveFile_MetaList* MetaListTest = Cast<USaveFile_MetaList>(UGameplayStatics::LoadGameFromSlot("MetaList", 0));

	// First Check.
	// If the MetaList isn't set, attempt to load the save file.
	if (MetaListReference == nullptr)
		MetaListReference = Cast<USaveFile_MetaList>(UGameplayStatics::LoadGameFromSlot("MetaList", 0));

	// Second Check.
	// If the MetaList still isn't set, then it must be created.
	if (MetaListReference == nullptr) {
		MetaListReference = Cast<USaveFile_MetaList>(UGameplayStatics::CreateSaveGameObject(USaveFile_MetaList::StaticClass()));

		if (UGameplayStatics::SaveGameToSlot(MetaListReference, "MetaList", 0)) {
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, FString::Printf(TEXT("Warning: MetaList not detected. Creating new MetaList.")));
			UE_LOG(LogTemp, Warning, TEXT("Warning: MetaList not detected. Creating new MetaList."));
			return MetaListReference;
		}
		else {
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Error: MetaList not detected. Could not create new MetaList.")));
			UE_LOG(LogTemp, Error, TEXT("Error: MetaList not detected. Could not create new MetaList."));
			return nullptr;
		}
	}

	if (MetaListReference)
		return MetaListReference;
	else
		return nullptr;
}


void UTheHazards_GameInstance::LoadSaveFile(FString SaveFileSlotName)
{
	FAsyncLoadGameFromSlotDelegate LoadDelegate;
	TArray<ULevel*> FoundLevels;

	//LatentActionInfo.CallbackTarget = this;
	//LatentActionInfo.ExecutionFunction = "LoadSaveFilePartTwo";
	//LatentActionInfo.UUID = 1;
	//LatentActionInfo.Linkage = 1;

	SaveSlotName = SaveFileSlotName;

	if (!MetaListReference)
		MetaListReference = Cast<USaveFile_MetaList>(UGameplayStatics::LoadGameFromSlot("MetaList", 0));

	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, FString::Printf(TEXT("Warning: Attempting to load save file: %s"), *SaveSlotName));
	UE_LOG(LogTemp, Warning, TEXT("Warning: Attempting to load save file: %s"), *SaveSlotName);

	for (TObjectIterator<UUserWidget> Itr; Itr; ++Itr) {
		UUserWidget* FoundWidget = *Itr;

		FoundWidget->RemoveFromParent();
	}

	if (LoadScreen_Class) {
		LoadScreen_Widget = CreateWidget<UBaseClass_Widget_LoadScreen>(GetWorld(), LoadScreen_Class);
		LoadScreen_Widget->AddToViewport();
	}

	//TickActor_Entity_Reference = GetWorld()->SpawnActor<ATheHazards_GameInstance_TActor>(TickActor_Entity_Class, FVector::ZeroVector, FRotator::ZeroRotator);

	//if (SlotReference) {
	//	if (WorldReference->GetName() != SlotReference->LevelName) {
	//		UGameplayStatics::UnloadStreamLevel(WorldReference, FName(WorldReference->GetName()), LatentActionInfo, false);
	//		UGameplayStatics::LoadStreamLevel(WorldReference, FName(SlotReference->LevelName), true, false, LatentActionInfo);
	//	}
	//} else {
	//	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Error: Failed to load slot level.")));
	//	UE_LOG(LogTemp, Error, TEXT("Error: Failed to load slot level."));
	//}

	//if (WorldReference->GetName() != MetaListReference->SaveFileAndLevelNames.FindRef(SaveFileSlotName)) {
	//FString FoundLevelName = MetaListReference->SaveFileAndLevelNames.FindRef(SaveSlotName);

	//Get and Unload all streamed levels
	//for (TObjectIterator<ULevel> Itr; Itr; ++Itr) {
	//	ULevel* FoundLevel = *Itr;
	//	if (!FoundLevel->GetFullName().Contains("MasterLevel")) {
	//		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, FString::Printf(TEXT("Message: Unload level %s"), *FoundLevel->GetFullName()));
	//		UE_LOG(LogTemp, Display, TEXT("Message: Unload level %s"), *FoundLevel->GetFullName());

	//		UGameplayStatics::UnloadStreamLevel(this, FName(FoundLevel->GetFullName()), LatentActionInfo, false);
	//	} else {
	//		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, FString::Printf(TEXT("Message: Found level %s"), *FoundLevel->GetFullName()));
	//		UE_LOG(LogTemp, Display, TEXT("Message: Found level %s"), *FoundLevel->GetFullName());
	//	}
	//}
	const TArray<ULevelStreaming*>& StreamedLevels = GetWorld()->GetStreamingLevels();

	for (auto& Level : StreamedLevels) {
		if (Level->IsLevelLoaded()) {
			Level->SetIsRequestingUnloadAndRemoval(true);
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, FString::Printf(TEXT("Message: Unload level %s"), *Level->GetWorldAssetPackageName()));
		}
	}

	UGameplayStatics::LoadStreamLevel(this, TEXT("TestThree_Streaming"), true, true, LatentActionInfo);

	//FString MapName = (GetWorld()->GetMapName());
	//if (GetWorld())
	//	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, GetWorld()->GetMapName());
	//else 
	//	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Error: Failed to GetWorld().")));

	//if (GetWorld())
	//World'/Game/Levels/TestTwo.TestTwo'
	//UGameplayStatics::UnloadStreamLevel(this, "TestTwo", LatentActionInfo, true);
	//LoadSaveFilePartTwo();

	//else {
	//	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Error: Failed to GetWorld().")));
	//	UE_LOG(LogTemp, Error, TEXT("Error: Failed to GetWorld()."));
	//}

	UGameplayStatics::SetGamePaused(GetWorld(), false);

	SlotReference = Cast<USaveFile_Slot>(UGameplayStatics::CreateSaveGameObject(USaveFile_Slot::StaticClass()));
	LoadDelegate.BindUObject(SlotReference, &USaveFile_Slot::LoadGameDelegateFunction);
	SlotReference->GameInstanceReference = this;
	UGameplayStatics::AsyncLoadGameFromSlot(SaveSlotName, 0, LoadDelegate);
}


void UTheHazards_GameInstance::LoadSaveFilePartTwo()
{
	FAsyncLoadGameFromSlotDelegate LoadDelegate;
	//ULevelStreaming* StreamLevel;

	LatentActionInfo.ExecutionFunction = "LoadSaveFilePartThree";
	LatentActionInfo.UUID = 12345;

	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, FString::Printf(TEXT("Message: Call LoadSaveFilePartTwo()")));
	UE_LOG(LogTemp, Display, TEXT("Message: Call LoadSaveFilePartTwo()"));

	//StreamLevel = UGameplayStatics::GetStreamingLevel(this, "TestThree_Streaming");

	//while (StreamLevel != nullptr && StreamLevel->GetLoadedLevel() == nullptr)
	//{
	//	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, FString::Printf(TEXT("Loading Level...")));
	//	UE_LOG(LogTemp, Display, TEXT("Loading Level..."));
	//}

	// Destroy all objects and widgets(?)

	// Load the save file
	// Save file needs a second delegate function that returns the save file. (?)
	// Save files must be loaded after the level is loaded ?

	//UKismetSystemLibrary::Delay(this, 1.f, LatentActionInfo);

	//LoadSaveFilePartThree();

	//// Begin Minimum time delay for clearing the loading screen
	//if (GetWorld()) {
	//	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, FString::Printf(TEXT("Message: GetWorld() succeeded?")));
	//	//UE_LOG(LogTemp, Warning, TEXT("Message: GetWorld() succeeded?"));

	//	//GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UTheHazards_GameInstance::ClearLoadingScreen, 0.25f);
	//	//UKismetSystemLibrary::Delay(this, 2.5f, LatentActionInfo);
	//	//ClearLoadingScreen();


	//	if (TickActor_Entity_Reference) {
	//		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, FString::Printf(TEXT("Message: TickActor_Entity is valid.")));
	//		UE_LOG(LogTemp, Display, TEXT("Message: TickActor_Entity is valid."));
	//	}
	//	else {
	//		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Error: TickActor_Entity not valid.")));
	//		UE_LOG(LogTemp, Error, TEXT("Error: TickActor_Entity not valid."));
	//	}
	//}
	//else {
	//	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Error: GetWorld() failed.")));
	//	UE_LOG(LogTemp, Error, TEXT("Error: GetWorld() failed."));
	//}

	// Spawn Player
	TArray<AActor*> PlayerStartActors;
	TArray<AActor*> PlayerActors;
	FActorSpawnParameters ActorSpawnParameters;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), PlayerStartActors);
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEntity_Player::StaticClass(), PlayerActors);

	for (auto& Player : PlayerActors) {
		Player->Destroy();
	}

	for (int i = 0; i < PlayerStartActors.Num(); i++) {
		if (PlayerStartActors.IsValidIndex(i)) {
			ABaseClass_PlayerController* PlayerControllerRef = Cast<ABaseClass_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));

			Player_Entity_Reference = GetWorld()->SpawnActor<AEntity_Player>(Player_Entity_Class, PlayerStartActors[i]->GetActorLocation(), PlayerStartActors[i]->GetActorRotation(), ActorSpawnParameters);
			PlayerControllerRef->Possess(Player_Entity_Reference);
			Player_Entity_Reference->Player_Controller_Reference = PlayerControllerRef;
			//Player_Entity_Reference->ManualBeginPlay();

			//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, FString::Printf(TEXT("Possess Player?")));
			//UE_LOG(LogTemp, Display, TEXT("Possess Player?"));

			//Unpause game here
			//
			//Player_Entity_Reference->ClearLoadingScreenTimer();

			break;
		}
	}

	//Set main menu mode
	Cast<ABaseClass_PlayerController>(GetWorld()->GetFirstPlayerController())->MainMenuMode = false;
}


void UTheHazards_GameInstance::LoadSaveFilePartThree()
{
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, FString::Printf(TEXT("Message: Call LoadSaveFilePartThree()")));
	UE_LOG(LogTemp, Display, TEXT("Message: Call LoadSaveFilePartThree()"));

	TArray<AActor*> TickActors;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATheHazards_GameInstance_TActor::StaticClass(), TickActors);

	for (int i = 0; i < TickActors.Num(); i++) {
		if (TickActors.IsValidIndex(i)) {
			Cast<ATheHazards_GameInstance_TActor>(TickActors[i])->ClearLoadingScreenBegin();
			break;
		}
	}

	//if (TickActor_Entity_Reference) {
	//	TickActor_Entity_Reference->GameInstanceReference = this;
	//	TickActor_Entity_Reference->LoadSaveFileDelayFunction();
	//}
	//else {
	//	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Error: TickActorReference not valid.")));
	//	UE_LOG(LogTemp, Error, TEXT("Error: TickActorReference not valid."));
	//}
}


void UTheHazards_GameInstance::LoadSaveFilePartFour()
{
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, FString::Printf(TEXT("Message: Call LoadSaveFilePartFour()")));
	UE_LOG(LogTemp, Display, TEXT("Message: Call LoadSaveFilePartFour()"));

	// Clear Loading Screen(s)
	for (TObjectIterator<UBaseClass_Widget_LoadScreen> Itr; Itr; ++Itr) {
		UBaseClass_Widget_LoadScreen* FoundWidget = *Itr;
		FoundWidget->RemoveFromParent();
	}

	//if (LoadScreen_Widget)
	//	LoadScreen_Widget->RemoveFromParent();
}