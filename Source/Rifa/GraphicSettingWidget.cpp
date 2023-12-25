// Fill out your copyright notice in the Description page of Project Settings.


#include "GraphicSettingWidget.h"
#include "Components/Button.h"
#include "RifaCharacter.h"
#include "GameFramework/GameUserSettings.h"

void UGraphicSettingWidget::FirstConstruct()
{
	ReturnButton = Cast<UButton>(GetWidgetFromName(TEXT("ReturnButton")));
	ReturnButton->OnClicked.AddDynamic(this, &UGraphicSettingWidget::CloseWidget);
}

void UGraphicSettingWidget::Init()
{
	Super::Init();
}

void UGraphicSettingWidget::CloseWidget()
{
	Super::CloseWidget();
}
