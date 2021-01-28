#include "BaseClass_Widget_DevMenu.h"

#include "Entity_Player.h"
#include "Engine/LevelStreaming.h"
#include "TheHazards_GameInstance.h"


// ------------------------- Widgets
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

		//if (Level->IsLevelLoaded()) {
		//	SwitchLevel_DropDown->SetSelectedOption(SplitLevelName);
		//}
	}
}


void UBaseClass_Widget_DevMenu::UpdateVariables()
{
	if (!PlayerReference) {
		PlayerReference = Cast<AEntity_Player>(GetWorld()->GetFirstPlayerController()->GetPawn());
	}

	if (PlayerReference) {
		PlayerLevelText->SetText(FText::FromString(FString::FromInt(PlayerReference->Level)));
	}
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

	LatentActionInfo.CallbackTarget = this;
	LatentActionInfo.ExecutionFunction = "LoadLevel";
	LatentActionInfo.UUID = 1345;
	LatentActionInfo.Linkage = 1;

	//if () {
	for (auto& Level : StreamedLevels) {
		Level->GetWorldAssetPackageName().Split("/Game/Levels/", &LeftSplit, &SplitLevelName);

		if (Level->IsLevelVisible()) {
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, FString::Printf(TEXT("Message: Unload level %s"), *Level->GetWorldAssetPackageName()));
			UE_LOG(LogTemp, Warning, TEXT("Message: Unload level %s"), *Level->GetWorldAssetPackageName());

			UGameplayStatics::UnloadStreamLevel(this, Level->GetWorldAssetPackageFName(), LatentActionInfo, false);
		}
	}

	// Load the new level via the GameInstance
	//Cast<UTheHazards_GameInstance>(GetWorld()->GetGameInstance())->DevMenu_LoadLevel(SwitchLevel_DropDown->GetSelectedOption());
}


void UBaseClass_Widget_DevMenu::LoadLevel()
{
	FLatentActionInfo LatentActionInfo;

	UGameplayStatics::LoadStreamLevel(GetWorld(), FName(SwitchLevel_DropDown->GetSelectedOption()), true, false, LatentActionInfo);
}