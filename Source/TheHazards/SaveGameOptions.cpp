#include "SaveGameOptions.h"


#include "Runtime/JsonUtilities/Public/JsonObjectConverter.h"
#include "WidgetMenuOptions.h"


void USaveGameOptions::SaveOptionsToJson(FOptionsData InOptionsData, FString PlayerName)
{
	// Get the project's save folder directory
	PlayerDataSaveFilePath = FPaths::ProjectSavedDir();
	UE_LOG(LogTemp, Warning, TEXT("FilePaths: ProjectSavedDir: %s"), *PlayerDataSaveFilePath);
	PlayerDataSaveFilePath.Append(PlayerName);
	UE_LOG(LogTemp, Warning, TEXT("FilePaths: Player's Save Data Folder: %s"), *PlayerDataSaveFilePath);

	FString OptionsDataAsJson;
	FJsonObjectConverter::UStructToJsonObjectString(OptionsData, OptionsDataAsJson, 0, 0);

	IPlatformFile& FileManager = FPlatformFileManager::Get().GetPlatformFile();
	bool OverwriteFile = true;

	if (!FileManager.DirectoryExists(*PlayerDataSaveFilePath)) {
		if (FileManager.CreateDirectory(*PlayerDataSaveFilePath)) {
			UE_LOG(LogTemp, Warning, TEXT("Player's Save Data Folder did not exist but was created successfully."));
		} else {
			UE_LOG(LogTemp, Error, TEXT("Player's Save Data Folder did not exist and could not be created."));
		}
	}

	if (FileManager.DirectoryExists(*PlayerDataSaveFilePath)) {
		FString FileName = PlayerDataSaveFilePath.Append("/Options.json");
		UE_LOG(LogTemp, Warning, TEXT("FilePaths: Player's Options File: %s"), *FileName);

		if (FFileHelper::SaveStringToFile(OptionsDataAsJson, *FileName)) {
			UE_LOG(LogTemp, Warning, TEXT("Player's options saves successfully."));
		} else {
			UE_LOG(LogTemp, Error, TEXT("Error: Failed to save Player's options."));
		}
	} else {
		UE_LOG(LogTemp, Error, TEXT("Error: Could not save Player's options."));
	}
}