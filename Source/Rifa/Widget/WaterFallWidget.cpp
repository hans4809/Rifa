// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/WaterFallWidget.h"
#include <Kismet/GameplayStatics.h>
#include "Data/MyGameInstance.h"

void UWaterFallWidget::Init()
{
	Super::Init();
	SetInputActionPriority(Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->PopupSort);
	AddToViewport(Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->PopupSort++);
}

void UWaterFallWidget::CloseWidget()
{
	Super::CloseWidget();
	Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->PopupSort--;
	RemoveFromParent();
}
