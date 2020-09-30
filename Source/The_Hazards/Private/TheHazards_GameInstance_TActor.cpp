#include "TheHazards_GameInstance_TActor.h"

#include "TimerManager.h"
#include "TheHazards_GameInstance.h"
#include "BaseClass_Widget_LoadScreen.h"


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

	//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, FString::Printf(TEXT("Tick?")));
	//UE_LOG(LogTemp, Display, TEXT("Tick?"));

	if (GetWorld()->GetTimerManager().IsTimerActive(TimerHandle)) {
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, FString::Printf(TEXT("Message: Timer is active. Time Remaining: %f"), GetWorldTimerManager().GetTimerRemaining(TimerHandle)));
		UE_LOG(LogTemp, Display, TEXT("Message: Timer is active. Time Remaining: %f"), GetWorldTimerManager().GetTimerRemaining(TimerHandle));
	}
}


void ATheHazards_GameInstance_TActor::ClearLoadingScreenTimer()
{
	//GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ATheHazards_GameInstance_TActor::ClearLoadingScreenFunction, 1.f, false, 1.f);
	GetWorldTimerManager().SetTimer(TimerHandle, this, &ATheHazards_GameInstance_TActor::ClearLoadingScreenFunction, 1.f, false, 1.f);

	if (GetWorld()->GetTimerManager().IsTimerActive(TimerHandle)) {
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, FString::Printf(TEXT("Message: Timer is active.")));
		UE_LOG(LogTemp, Display, TEXT("Message: Timer is active."));
	}
	else {
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Error: Timer not valid")));
		UE_LOG(LogTemp, Error, TEXT("Error: Timer not valid."));
	}
}


void ATheHazards_GameInstance_TActor::ClearLoadingScreenFunction()
{
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, FString::Printf(TEXT("Message: Timer is active.")));
	UE_LOG(LogTemp, Display, TEXT("Message: Timer is active."));

	if (!GameInstanceReference)
		GameInstanceReference = Cast<UTheHazards_GameInstance>(GetWorld()->GetGameInstance());

	GameInstanceReference->ClearLoadingScreen();

	//if (GameInstanceReference)
	//	GameInstanceReference->ClearLoadingScreen();
	//else {
	//	GameInstanceReference = <UTheHazards_GameInstance>(GetWorld()->GetGameInstance());
	//	GameInstanceReference->ClearLoadingScreen();
	//}

	Destroy();
}