// Fill out your copyright notice in the Description page of Project Settings.


#include "RifaMainHUD.h"
#include "Components/Button.h"
#include "MainSettingWidget.h"

void URifaMainHUD::NativeConstruct()
{
	Super::NativeConstruct();
	ResetButton = Cast<UButton>(GetWidgetFromName(TEXT("ResetButton")));
	LoadButton = Cast<UButton>(GetWidgetFromName(TEXT("LoadButton")));
	SettingButton = Cast<UButton>(GetWidgetFromName(TEXT("SettingButton")));
	QuitButton = Cast<UButton>(GetWidgetFromName(TEXT("QuitButton")));
	SettingButton->OnClicked.AddDynamic(this, &URifaMainHUD::SettingButtonClicked);
}

void URifaMainHUD::Init()
{
	Super::Init();
}

void URifaMainHUD::SettingButtonClicked()
{
	if (IsValid(MainSettingWidgetClass))
	{
		MainSettingWidgetAsset = Cast<UMainSettingWidget>(CreateWidget(GetWorld(), MainSettingWidgetClass));
	}
	MainSettingWidgetAsset->Init();
}
