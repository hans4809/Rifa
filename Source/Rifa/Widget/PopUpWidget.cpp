// Fill out your copyright notice in the Description page of Project Settings.


#include "PopUpWidget.h"
#include "Data/MyGameInstance.h"
#include <Kismet/GameplayStatics.h>

void UPopUpWidget::Init()
{
	Super::Init();
	SetInputActionPriority(Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->PopupSort);
	AddToViewport(Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->PopupSort++);
}

void UPopUpWidget::CloseWidget()
{
	Super::CloseWidget();
	Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->PopupSort--;
	RemoveFromParent();
}