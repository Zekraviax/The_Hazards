#include "SaveGamePlayerData.h"


#include "ActorComponentBaseData.h"
#include "Engine/World.h"
#include "EntityBaseCharacter.h"
#include "EntityPlayerCharacter.h"
#include "Runtime/JsonUtilities/Public/JsonObjectConverter.h"
#include "TheHazardsGameInstance.h"
#include "TheHazardsPlayerController.h"


void USaveGamePlayerData::SavePlayerDataToJson()
{
	if (PlayerEntityReference == NULL) {
		PlayerEntityReference = Cast<ATheHazardsPlayerController>(GetWorld()->GetFirstPlayerController())->GetPawnAsEntityPlayerCharacter();
	}

	// Get the project's save folder directory
	PlayerDataSaveFilePath = FPaths::ProjectSavedDir();
	UE_LOG(LogTemp, Warning, TEXT("FilePaths: ProjectSavedDir: %s"), *PlayerDataSaveFilePath);
	PlayerDataSaveFilePath.Append(PlayerData.Name);
	UE_LOG(LogTemp, Warning, TEXT("FilePaths: Player's Save Data Folder: %s"), *PlayerDataSaveFilePath);

	FString PlayerDataAsJson;

	//PlayerData.Name = PlayerEntity->GetBaseDataComponent()->Name;
	PlayerData.Transform = PlayerEntityReference->GetActorTransform();
	PlayerData.ControllerRotation = PlayerEntityReference->GetControlRotation();

	FJsonObjectConverter::UStructToJsonObjectString(PlayerData, PlayerDataAsJson, 0, 0);
	
	// Before we save the json file, we need to check if the player's save data folder exists
	// If it doesn't, we make it first
	// The directory path should be PlayerDataSaveFilePath + the player character's name
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
		FString FileName = PlayerDataSaveFilePath.Append("/Player.json");
		UE_LOG(LogTemp, Warning, TEXT("FilePaths: Player's Save Data File: %s"), *FileName);

		if (FFileHelper::SaveStringToFile(PlayerDataAsJson, *FileName)) {
			UE_LOG(LogTemp, Warning, TEXT("Player's data saves successfully."));
		} else {
			UE_LOG(LogTemp, Error, TEXT("Error: Failed to save Player's data."));
		}
	} else {
		UE_LOG(LogTemp, Error, TEXT("Error: Could not save Player's data."));
	}

	//BeginDestroy();
}


void USaveGamePlayerData::LoadPlayerDataFromJson(AEntityBaseCharacter* PlayerEntity, FString PlayerSaveDataFolderName)
{
	IPlatformFile& FileManager = FPlatformFileManager::Get().GetPlatformFile();
	PlayerSaveDataFolderName = PlayerEntity->GetBaseDataComponent()->Name;

	PlayerDataSaveFilePath = FPaths::ProjectSavedDir();
	PlayerDataSaveFilePath.Append(PlayerSaveDataFolderName);
	UE_LOG(LogTemp, Warning, TEXT("FilePaths: Player's Save Data Folder: %s"), *PlayerDataSaveFilePath);

	FString FileName = PlayerDataSaveFilePath.Append("/Player.json");
	UE_LOG(LogTemp, Warning, TEXT("FilePaths: Player's Save Data File: %s"), *FileName);

	if (!FPlatformFileManager::Get().GetPlatformFile().FileExists(*PlayerDataSaveFilePath)) {
		UE_LOG(LogTemp, Error, TEXT("Error: Could not find Player's data."));
		return;
	}

	FString PlayerDataAsJson;
	FEntityBaseData PlayerDataAsStruct;

	FFileHelper::LoadFileToString(PlayerDataAsJson, *FileName);
	FJsonObjectConverter::JsonObjectStringToUStruct(PlayerDataAsJson, &PlayerDataAsStruct, 0, 0);

	// Apply player data
	PlayerEntity->GetBaseDataComponent()->Name = PlayerDataAsStruct.Name;
	PlayerEntity->SetActorTransform(PlayerDataAsStruct.Transform);
	PlayerEntity->GetController()->SetControlRotation(PlayerDataAsStruct.ControllerRotation);

	// To-Do: Close the pause menu and unpause the level
	//BeginDestroy();
}