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
	TArray<ULevel*> FoundLevels;

	SaveSlotName = SaveFileSlotName;

	if (!MetaListReference)
		MetaListReference = Cast<USaveFile_MetaList>(UGameplayStatics::LoadGameFromSlot("MetaList", 0));

	// Clear all widgets
	for (TObjectIterator<UUserWidget> Itr; Itr; ++Itr) {
		UUserWidget* FoundWidget = *Itr;
		FoundWidget->RemoveFromParent();
	}

	// Loading Screen
	if (LoadScreen_Class) {
		LoadScreen_Widget = CreateWidget<UBaseClass_Widget_LoadScreen>(GetWorld(), LoadScreen_Class);
		LoadScreen_Widget->AddToViewport();
	}

	UGameplayStatics::SetGamePaused(GetWorld(), false);

	// Clear all levels except the MasterLevel
	const TArray<ULevelStreaming*>& StreamedLevels = GetWorld()->GetStreamingLevels();

	for (auto& Level : StreamedLevels) {
		if (Level->IsLevelLoaded()) {
			Level->SetIsRequestingUnloadAndRemoval(true);
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, FString::Printf(TEXT("Message: Unload level %s"), *Level->GetWorldAssetPackageName()));
			UE_LOG(LogTemp, Warning, TEXT("Message: Unload level %s"), *Level->GetWorldAssetPackageName());
		}
	}

	// Load the player's Save File
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, FString::Printf(TEXT("Warning: Attempting to load save file: %s"), *SaveSlotName));
	UE_LOG(LogTemp, Warning, TEXT("Warning: Attempting to load save file: %s"), *SaveSlotName);

	SlotReference = Cast<USaveFile_Slot>(UGameplayStatics::CreateSaveGameObject(USaveFile_Slot::StaticClass()));
	LoadDelegate.BindUObject(SlotReference, &USaveFile_Slot::LoadGameDelegateFunction);
	SlotReference->GameInstanceReference = this;
	UGameplayStatics::AsyncLoadGameFromSlot(SaveSlotName, 0, LoadDelegate);
}


void UTheHazards_GameInstance::LoadSaveFilePartTwo()
{
	LatentActionInfo.CallbackTarget = this;
	LatentActionInfo.ExecutionFunction = "LoadSaveFilePartThree";
	LatentActionInfo.UUID = 12345;
	LatentActionInfo.Linkage = 1;

	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, FString::Printf(TEXT("Message: Call LoadSaveFilePartTwo()")));
	UE_LOG(LogTemp, Display, TEXT("Message: Call LoadSaveFilePartTwo()"));

	// Load the Save File's level
	UGameplayStatics::LoadStreamLevel(this, TEXT("TestThree_Streaming"), true, false, LatentActionInfo);
}


void UTheHazards_GameInstance::LoadSaveFilePartThree()
{
	TArray<AActor*> PlayerActors, TickActors;
	FActorSpawnParameters ActorSpawnParameters;

	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, FString::Printf(TEXT("Message: Call LoadSaveFilePartThree()")));
	UE_LOG(LogTemp, Display, TEXT("Message: Call LoadSaveFilePartThree()"));

	// Find all currently existing Player actors
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEntity_Player::StaticClass(), PlayerActors);

	for (int i = 0; i < PlayerActors.Num(); i++) {
		if (PlayerActors.IsValidIndex(i)) {
			Player_Entity_Reference = Cast<AEntity_Player>(PlayerActors[i]);
			Cast<ABaseClass_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0))->Possess(Player_Entity_Reference);
			break;
		}
	}

	//Set main menu mode
	Cast<ABaseClass_PlayerController>(GetWorld()->GetFirstPlayerController())->MainMenuMode = false;

	// Set Player Data
	// Location in world
	Player_Entity_Reference->SetActorLocationAndRotation(SlotReference->PlayerReference->GetActorLocation(), SlotReference->PlayerReference->GetActorRotation());

	// Set Entity Data

	// Begin the minimum delay for clearing the loading screen
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATheHazards_GameInstance_TActor::StaticClass(), TickActors);
	for (int i = 0; i < TickActors.Num(); i++) {
		if (TickActors.IsValidIndex(i)) {
			Cast<ATheHazards_GameInstance_TActor>(TickActors[i])->ClearLoadingScreenBegin();
			break;
		}
	}
}


void UTheHazards_GameInstance::LoadSaveFilePartFour()
{
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, FString::Printf(TEXT("Message: Call LoadSaveFilePartFour()")));
	UE_LOG(LogTemp, Display, TEXT("Message: Call LoadSaveFilePartFour()"));
}