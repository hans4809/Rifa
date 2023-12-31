// Fill out your copyright notice in the Description page of Project Settings.


#include "MainSettingWidget.h"
#include "Components/Button.h"
#include "SoundSettingWidget.h"
#include "InputSettingWidget.h"
#include "GraphicSettingWidget.h"

void UMainSettingWidget::NativeConstruct()
{
	Super::NativeConstruct();
	SoundButton = Cast<UButton>(GetWidgetFromName(TEXT("SoundButton")));
	GraphicButton = Cast<UButton>(GetWidgetFromName(TEXT("GraphicButton")));
	ControlButton = Cast<UButton>(GetWidgetFromName(TEXT("ControlButton")));
	ReturnButton = Cast<UButton>(GetWidgetFromName(TEXT("ReturnButton")));
	ReturnButton->OnClicked.AddDynamic(this, &UMainSettingWidget::CloseWidget);
	SoundButton->OnClicked.AddDynamic(this, &UMainSettingWidget::SoundButtonClicked);
	GraphicButton->OnClicked.AddDynamic(this, &UMainSettingWidget::GraphicButtonClicked);
	ControlButton->OnClicked.AddDynamic(this, &UMainSettingWidget::InputButtonClicked);
}

void UMainSettingWidget::Init()
{
	Super::Init();
}

void UMainSettingWidget::CloseWidget()
{
	Super::CloseWidget();
}

void UMainSettingWidget::SoundButtonClicked()
{
	if (IsValid(SoundSettingWidgetClass))
	{
		SoundSettingWidgetAsset = Cast<USoundSettingWidget>(CreateWidget(GetWorld(), SoundSettingWidgetClass));
	}
	SoundSettingWidgetAsset->Init();
}

void UMainSettingWidget::GraphicButtonClicked()
{
	if (IsValid(GraphicSettingWidgetClass))
	{
		GraphicSettingWidgetAsset = Cast<UGraphicSettingWidget>(CreateWidget(GetWorld(), GraphicSettingWidgetClass));
	}
	GraphicSettingWidgetAsset->Init();
}

void UMainSettingWidget::InputButtonClicked()
{
	if (IsValid(InputSettingWidgetClass))
	{
		InputSettingWidgetAsset = Cast<UInputSettingWidget>(CreateWidget(GetWorld(), InputSettingWidgetClass));
	}
	InputSettingWidgetAsset->Init();
}
