#include "TheHazardsGameInstance.h"


#include "EntityPlayerCharacter.h"
#include "Kismet/GameplayStatics.h"


void UTheHazardsGameInstance::Init()
{
	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("UTheHazardsGameInstance / Init / Game Instance Initiated")));
	PlayerSaveObject = Cast<USaveGamePlayerData>(UGameplayStatics::CreateSaveGameObject(USaveGamePlayerData::StaticClass()));
	OptionsSaveObject = Cast<USaveGameOptions>(UGameplayStatics::CreateSaveGameObject(USaveGameOptions::StaticClass()));
}