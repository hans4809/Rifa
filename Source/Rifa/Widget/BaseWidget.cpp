// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseWidget.h"
#include "Components/PanelSlot.h"
#include "LevelScript/BaseLevelScriptActor.h"

void UBaseWidget::Init()
{
	CurrentLevelScriptActor = Cast<ABaseLevelScriptActor>(GetWorld()->GetLevelScriptActor());
}

void UBaseWidget::CloseWidget()
{
}
