#include "BaseClass_Widget_DevMenu.h"

#include "Entity_Player.h"
#include "Engine/LevelStreaming.h"


// ------------------------- Widget
void UBaseClass_Widget_DevMenu::OpenWidget()
{
	if (!PlayerReference) {
		PlayerReference = Cast<AEntity_Player>(GetWorld()->GetFirstPlayerController()->GetPawn());
	}

	UpdateVariables();

	// Add all levels to the SwitchLevel DropDown
	const TArray<ULevelStreaming*>& StreamedLevels = GetWorld()->GetStreamingLevels();

	// Get the Streamed Level Name, not the Master Level name
	for (auto& Level : StreamedLevels) {
		FString LeftSplit, SplitLevelName;
		Level->GetWorldAssetPackageName().Split("/Game/Levels/", &LeftSplit, &SplitLevelName);

		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, FString::Printf(TEXT("Message: Found level: %s"), *SplitLevelName));
		UE_LOG(LogTemp, Warning, TEXT("Message: Found level: %s"), *SplitLevelName);

		SwitchLevel_DropDown->AddOption(SplitLevelName);

		if (Level->IsLevelLoaded()) {
			SwitchLevel_DropDown->SetSelectedOption(SplitLevelName);
		}
	}
}


void UBaseClass_Widget_DevMenu::UpdateVariables()
{
	if (!PlayerReference) {
		PlayerReference = Cast<AEntity_Player>(GetWorld()->GetFirstPlayerController()->GetPawn());
	}

	PlayerLevelText->SetText(FText::FromString(FString::FromInt(PlayerReference->Level)));
}


// ------------------------- Functions
void UBaseClass_Widget_DevMenu::ChangePlayerLevel(int LevelChangeValue)
{
	if (!PlayerReference) {
		PlayerReference = Cast<AEntity_Player>(GetWorld()->GetFirstPlayerController()->GetPawn());
	}

	PlayerReference->Level += LevelChangeValue;
	UpdateVariables();
}


void UBaseClass_Widget_DevMenu::OnSwitchLevelDropdownChanged()
{
	// Unload all currently loaded levels
//	bool SwitchLevelOptionIsCurrentLevel;
	FLatentActionInfo LatentActionInfo;
	FString LeftSplit, SplitLevelName;
	const TArray<ULevelStreaming*>& StreamedLevels = GetWorld()->GetStreamingLevels();

	//if () {
	for (auto& Level : StreamedLevels) {
		Level->GetWorldAssetPackageName().Split("/Game/Levels/", &LeftSplit, &SplitLevelName);

		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, FString::Printf(TEXT("Message: Unload level %s"), *Level->GetWorldAssetPackageName()));
		UE_LOG(LogTemp, Warning, TEXT("Message: Unload level %s"), *Level->GetWorldAssetPackageName());

		if (Level->IsLevelLoaded() && SplitLevelName != SwitchLevel_DropDown->GetSelectedOption()) {
			//Level->SetIsRequestingUnloadAndRemoval(true);
			UGameplayStatics::UnloadStreamLevel(this, Level->GetWorldAssetPackageFName(), LatentActionInfo, false);

			//for (TObjectIterator<AEntity_Player> Itr; Itr; ++Itr) {
			//	AEntity_Player* FoundActor = *Itr;

			//	if (FoundActor->IsValidLowLevel())
			//		FoundActor->Destroy();
			//}
		}
	}

	// Load the chosen level
	UGameplayStatics::LoadStreamLevel(this, FName(SwitchLevel_DropDown->GetSelectedOption()), true, false, LatentActionInfo);
	//}


		//for (auto& Level : StreamedLevels) {
		//	Level->GetWorldAssetPackageName().Split("/Game/Levels/", &LeftSplit, &SplitLevelName);

		//	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, FString::Printf(TEXT("Message: Unload level %s"), *Level->GetWorldAssetPackageName()));
		//	UE_LOG(LogTemp, Warning, TEXT("Message: Unload level %s"), *Level->GetWorldAssetPackageName());

		//	if (Level->IsLevelLoaded() && SplitLevelName != SwitchLevel_DropDown->GetSelectedOption()) {
		//		//Level->SetIsRequestingUnloadAndRemoval(true);
		//		UGameplayStatics::UnloadStreamLevel(this, Level->GetWorldAssetPackageFName(), LatentActionInfo, false);
		//	}
		//	else {
		//		SwitchLevelOptionIsCurrentLevel = true;
		//	}
		//}

		// Load the chosen level
		//if (!SwitchLevelOptionIsCurrentLevel)  
		//	UGameplayStatics::LoadStreamLevel(this, FName(SwitchLevel_DropDown->GetSelectedOption()), true, false, LatentActionInfo);
}


void UBaseClass_Widget_DevMenu::LoadNewLevel()
{

}