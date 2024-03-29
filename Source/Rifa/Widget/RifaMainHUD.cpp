// Fill out your copyright notice in the Description page of Project Settings.


#include "RifaMainHUD.h"
#include "Components/Button.h"
#include "MainSettingWidget.h"
#include "Sound/SoundBase.h"
#include "Sound/SoundCue.h"
#include <Kismet/GameplayStatics.h>
#include <Data/MyGameInstance.h>
#include "Widget/ResetDataQuestionWidget.h"

URifaMainHUD::URifaMainHUD(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void URifaMainHUD::NativeConstruct()
{
	Super::NativeConstruct();
	ResetButton = Cast<UButton>(GetWidgetFromName(TEXT("ResetButton")));
	LoadButton = Cast<UButton>(GetWidgetFromName(TEXT("LoadButton")));
	SettingButton = Cast<UButton>(GetWidgetFromName(TEXT("SettingButton")));
	QuitButton = Cast<UButton>(GetWidgetFromName(TEXT("QuitButton")));

	ResetButton->OnClicked.AddDynamic(this, &URifaMainHUD::ResetButtonClicked);
	QuitButton->OnClicked.AddDynamic(this, &URifaMainHUD::QuitButtonClicked);
	SettingButton->OnClicked.AddDynamic(this, &URifaMainHUD::SettingButtonClicked);
	LoadButton->OnClicked.AddDynamic(this, &URifaMainHUD::LoadButtonClicked);
	PlaySound(MainBGM);
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

void URifaMainHUD::LoadButtonClicked()
{
	auto GameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GameInstance) 
	{
		FName LevelName = GameInstance->CurrentLevelName;
		UGameplayStatics::OpenLevel(this, LevelName);
	}
}

void URifaMainHUD::ResetButtonClicked()
{
	if (IsValid(ResetDataQuestionWidgetClass))
	{
		ResetDataQuestionWidgetAsset = Cast<UResetDataQuestionWidget>(CreateWidget(GetWorld(), ResetDataQuestionWidgetClass));
		ResetDataQuestionWidgetAsset->Init();
	}
}

void URifaMainHUD::QuitButtonClicked()
{
	auto PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController)
	{
		PlayerController->ConsoleCommand("quit");
	}
}
