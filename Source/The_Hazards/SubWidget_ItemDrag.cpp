// Fill out your copyright notice in the Description page of Project Settings.


#include "SubWidget_ItemDrag.h"


void USubWidget_ItemDrag::NativeTick(const FGeometry& MyGeometry, float DeltaTime)
{
	Super::NativeTick(MyGeometry, DeltaTime);
}

void USubWidget_ItemDrag::SetPosition() 
{
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetMousePosition(MousePosX, MousePosY);
	SetPositionInViewport(FVector2D(MousePosX + 10, MousePosY + 10), true);
	GEngine->AddOnScreenDebugMessage(-1, 0.05f, FColor::White, TEXT("Mouse Pos " + FString::SanitizeFloat(MousePosX) + "  /  " + FString::SanitizeFloat(MousePosY)));
}