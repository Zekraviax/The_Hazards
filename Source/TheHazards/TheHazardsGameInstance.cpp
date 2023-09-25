#include "TheHazardsGameInstance.h"


#include "Kismet/GameplayStatics.h"


void UTheHazardsGameInstance::Init()
{
	//GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("UTheHazardsGameInstance / Init / Game Instance Initiated")));
	OptionsSaveObject = Cast<USaveGameOptions>(UGameplayStatics::CreateSaveGameObject(USaveGameOptions::StaticClass()));
}