// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseWidget.h"
#include "Components/PanelSlot.h"
#include "LevelScript/BaseLevelScriptActor.h"
#include "Data/MyGameInstance.h"
#include "Kismet/GameplayStatics.h"

void UBaseWidget::Init()
{
	CurrentLevelScriptActor = Cast<ABaseLevelScriptActor>(GetWorld()->GetLevelScriptActor());
	RifaGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
}

void UBaseWidget::CloseWidget()
{
}
