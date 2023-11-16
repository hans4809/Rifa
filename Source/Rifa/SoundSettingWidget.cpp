// Fill out your copyright notice in the Description page of Project Settings.


#include "SoundSettingWidget.h"
#include "Components/Button.h"

void USoundSettingWidget::NativeConstruct()
{
	Super::NativeConstruct();
	CollectionButton = Cast<UButton>(GetWidgetFromName(TEXT("CollectionButton")));
	///CollectionButton->OnClicked
}

void USoundSettingWidget::Init()
{
	Super::Init();
}

void USoundSettingWidget::CloseWidget()
{
	Super::CloseWidget();
}
