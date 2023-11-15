// Fill out your copyright notice in the Description page of Project Settings.


#include "MainSettingWidget.h"
#include "Components/Button.h"

void UMainSettingWidget::NativeConstruct()
{
	Super::NativeConstruct();
	SoundButton = Cast<UButton>(GetWidgetFromName(TEXT("SoundButton")));
	GraphicButton = Cast<UButton>(GetWidgetFromName(TEXT("GraphicButton")));
	ControlButton = Cast<UButton>(GetWidgetFromName(TEXT("ControlButton")));
	ReturnButton = Cast<UButton>(GetWidgetFromName(TEXT("ReturnButton")));
	ReturnButton->OnClicked.AddDynamic(this, &UMainSettingWidget::CloseWidget);
}

void UMainSettingWidget::Init()
{
	Super::Init();
}

void UMainSettingWidget::CloseWidget()
{
	Super::CloseWidget();
}
