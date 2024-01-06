// Fill out your copyright notice in the Description page of Project Settings.


#include "PickupText.h"
#include "Kismet/GameplayStatics.h"

void UPickupText::Init()
{
	Super::Init();
}

void UPickupText::CloseWidget()
{
	Super::CloseWidget();
}

void UPickupText::Tick(FGeometry MyGeometry, float InDeltaTime)
{
	Super::Tick(MyGeometry, InDeltaTime);
	//auto PlayerCotroller = Cast<APlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	//PlayerCotroller->ProjectWorldLocationToScreen(ViewPortPosition);
}
