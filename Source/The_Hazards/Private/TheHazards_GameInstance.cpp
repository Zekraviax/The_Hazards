#include "TheHazards_GameInstance.h"

#include "SaveFile_Slot.h"
#include "BaseClass_Widget_LoadScreen.h"
#include "BaseClass_PlayerController.h"
#include "TimerManager.h"
#include "GameFramework/SaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "Delegates/Delegate.h"


USaveFile_MetaList* UTheHazards_GameInstance::ReturnMetaList()
{
	USaveFile_MetaList* MetaListTest = Cast<USaveFile_MetaList>(UGameplayStatics::LoadGameFromSlot("MetaList", 0));

	if (MetaListTest == nullptr) {
		MetaListTest = Cast<USaveFile_MetaList>(UGameplayStatics::CreateSaveGameObject(USaveFile_MetaList::StaticClass()));

		if (UGameplayStatics::SaveGameToSlot(MetaListTest, "MetaList", 0)) {
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, FString::Printf(TEXT("Warning: MetaList not detected. Creating new MetaList.")));
			UE_LOG(LogTemp, Warning, TEXT("Warning: MetaList not detected. Creating new MetaList."));
			return MetaListTest;
		}
		else {
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Error: Could not create MetaList.")));
			UE_LOG(LogTemp, Error, TEXT("Error: Could not create MetaList."));
			return nullptr;
		}
	}
	else {
		return nullptr;
	}

	return nullptr;
}


void UTheHazards_GameInstance::LoadSaveFile(USaveFile_Slot* SlotReference, UWorld* WorldReference)
{
	TArray<UUserWidget*> WidgetsToRemove;
	FStreamableManager StreamableManager;
	FLatentActionInfo LatentActionInfo;
	FTimerHandle TimerHandle;
	UBaseClass_Widget_LoadScreen* LoadScreen_Widget;

	for (TObjectIterator<UUserWidget> Itr; Itr; ++Itr) {
		UUserWidget* FoundWidget = *Itr;
		WidgetsToRemove.Add(FoundWidget);
	}

	// Create and display a Loading Screen
	//if (LoadScreen_Class != NULL && GetWorld()->IsValidLowLevel()) {
	LoadScreen_Widget = CreateWidget<UBaseClass_Widget_LoadScreen>(WorldReference, UBaseClass_Widget_LoadScreen::StaticClass());
	LoadScreen_Widget->AddToViewport();
	//}

	for (auto Widget : WidgetsToRemove) {
		Widget->RemoveFromParent();
	}

	// load level
	UGameplayStatics::LoadStreamLevel(WorldReference, "TestTwo", true, false, LatentActionInfo);

	// Set main menu mode
	Cast<ABaseClass_PlayerController>(WorldReference->GetFirstPlayerController())->MainMenuMode = false;

	// Begin Minimum time delay for displaying the loading screen
	WorldReference->GetTimerManager().SetTimer(TimerHandle, this, &UTheHazards_GameInstance::ClearLoadingScreen, 0.2f);
}


void UTheHazards_GameInstance::ClearLoadingScreen()
{
	//for (TObjectIterator<UBaseClass_Widget_LoadScreen> Itr; Itr; ++Itr) {
	//	UBaseClass_Widget_LoadScreen* FoundWidget = *Itr;
	//	FoundWidget->RemoveFromParent();
	//}
}