// Fill out your copyright notice in the Description page of Project Settings.


#include "RifaMainHUD.h"
#include "Components/Button.h"
#include "MainSettingWidget.h"
#include "Sound/SoundBase.h"
#include "Sound/SoundCue.h"
#include <Kismet/GameplayStatics.h>
#include <Data/MyGameInstance.h>
#include "Widget/ResetDataQuestionWidget.h"
#include <Data/RIFASaveGame.h>

URifaMainHUD::URifaMainHUD(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	static ConstructorHelpers::FClassFinder<UUserWidget> MainSettingWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/BluePrint/UI/WG_MainSettingWidget.WG_MainSettingWidget_C'"));
	if (MainSettingWidget.Succeeded())
		MainSettingWidgetClass = MainSettingWidget.Class;

	static ConstructorHelpers::FClassFinder<UUserWidget> ResetDataQuestionWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/BluePrint/UI/WG_ResetDataQuestionWidget.WG_ResetDataQuestionWidget_C'"));
	if (ResetDataQuestionWidget.Succeeded())
		ResetDataQuestionWidgetClass = ResetDataQuestionWidget.Class;

	static ConstructorHelpers::FObjectFinder<USoundCue> MainBGMSound(TEXT("/Script/Engine.SoundCue'/Game/Sounds/GameBGM.GameBGM'"));
	if (MainBGMSound.Succeeded())
		MainBGM = MainBGMSound.Object;
}

void URifaMainHUD::NativeConstruct()
{
	Super::NativeConstruct();
	PlaySound(MainBGM);
	ResetButton = Cast<UButton>(GetWidgetFromName(TEXT("ResetButton")));
	LoadButton = Cast<UButton>(GetWidgetFromName(TEXT("LoadButton")));
	SettingButton = Cast<UButton>(GetWidgetFromName(TEXT("SettingButton")));
	QuitButton = Cast<UButton>(GetWidgetFromName(TEXT("QuitButton")));

	ResetButton->OnClicked.AddDynamic(this, &URifaMainHUD::ResetButtonClicked);
	QuitButton->OnClicked.AddDynamic(this, &URifaMainHUD::QuitButtonClicked);
	SettingButton->OnClicked.AddDynamic(this, &URifaMainHUD::SettingButtonClicked);
	LoadButton->OnClicked.AddDynamic(this, &URifaMainHUD::LoadButtonClicked);

	URIFASaveGame* RIFASaveGame = Cast<URIFASaveGame>(UGameplayStatics::LoadGameFromSlot("RIFASaveFile", 0));
	if (nullptr == RIFASaveGame)
		LoadButton->SetIsEnabled(false);
}

void URifaMainHUD::Init()
{
	Super::Init();
}

void URifaMainHUD::SettingButtonClicked()
{
	if (IsValid(MainSettingWidgetClass)&&!IsValid(MainSettingWidgetAsset))
	{
		MainSettingWidgetAsset = Cast<UMainSettingWidget>(CreateWidget(GetWorld(), MainSettingWidgetClass));
		if (IsValid(MainSettingWidgetAsset)) 
		{
			MainSettingWidgetAsset->ParentWidget = this;
			MainSettingWidgetAsset->Init();
		}
	}
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
	URIFASaveGame* RIFASaveGame = Cast<URIFASaveGame>(UGameplayStatics::LoadGameFromSlot("RIFASaveFile", 0));
	if (nullptr == RIFASaveGame)
	{
		LoadButtonClicked();
		return;
	}

	if (IsValid(ResetDataQuestionWidgetClass)&&!IsValid(ResetDataQuestionWidgetAsset))
	{
		ResetDataQuestionWidgetAsset = Cast<UResetDataQuestionWidget>(CreateWidget(GetWorld(), ResetDataQuestionWidgetClass));
		if (IsValid(ResetDataQuestionWidgetAsset))
		{
			ResetDataQuestionWidgetAsset->ParentWidget = this;
			ResetDataQuestionWidgetAsset->Init();
		}
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
