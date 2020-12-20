#include "TheHazards_GameInstance_TActor.h"

#include "TimerManager.h"
#include "TheHazards_GameInstance.h"
#include "BaseClass_Widget_LoadScreen.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values
ATheHazards_GameInstance_TActor::ATheHazards_GameInstance_TActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}


// Called when the game starts or when spawned
void ATheHazards_GameInstance_TActor::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void ATheHazards_GameInstance_TActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATheHazards_GameInstance_TActor::ClearLoadingScreenBegin()
{
	GetWorldTimerManager().SetTimer(ClearLoadingScreenTimerHandle, this, &ATheHazards_GameInstance_TActor::ClearLoadingScreenExecute, 2.f, false);

	//if (GetWorldTimerManager().IsTimerActive(ClearLoadingScreenTimerHandle)) {
	//	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, FString::Printf(TEXT("Message: ClearLoadingScreenTimer is active.")));
	//	UE_LOG(LogTemp, Display, TEXT("Message: ClearLoadingScreenTimer is active."));
	//}
	//else {
	//	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Error: ClearLoadingScreenTimer is not active.")));
	//	UE_LOG(LogTemp, Error, TEXT("Message: ClearLoadingScreenTimer is not active."));
	//}
}


void ATheHazards_GameInstance_TActor::ClearLoadingScreenExecute()
{
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, FString::Printf(TEXT("Message: Call ClearLoadingScreenExecute()")));
	UE_LOG(LogTemp, Display, TEXT("Message: Call ClearLoadingScreenExecute()"));

	// Clear the Loading Screen
	for (TObjectIterator<UBaseClass_Widget_LoadScreen> Itr; Itr; ++Itr) {
		UBaseClass_Widget_LoadScreen* FoundWidget = *Itr;
		FoundWidget->RemoveFromParent();
	}
}