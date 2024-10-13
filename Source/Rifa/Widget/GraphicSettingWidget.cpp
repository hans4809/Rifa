// Fill out your copyright notice in the Description page of Project Settings.


#include "GraphicSettingWidget.h"
#include "Components/Button.h"
#include "Character/RifaCharacter.h"
#include "GameFramework/GameUserSettings.h"

void UGraphicSettingWidget::NativeConstruct()
{
	Super::NativeConstruct();
	auto gameSettig = GEngine->GetGameUserSettings();
	gameSettig->LoadSettings();

	CurrentWindowMode = gameSettig->GetFullscreenMode();
	CurrentResolutions = gameSettig->GetScreenResolution();
	SetResolutionIndex(CurrentResolutions);
	
	FullScreenLeft = Cast<UButton>(GetWidgetFromName(TEXT("FullScreenLeft")));
	FullScreenRight = Cast<UButton>(GetWidgetFromName(TEXT("FullScreenRight")));
	ResolutionDown = Cast<UButton>(GetWidgetFromName(TEXT("ResolutionDown")));
	ResolutionUp = Cast<UButton>(GetWidgetFromName(TEXT("ResolutionUp")));
	ReturnButton = Cast<UButton>(GetWidgetFromName(TEXT("ReturnButton")));
	ApplyButton = Cast<UButton>(GetWidgetFromName(TEXT("ApplyButton")));

	FullScreenLeft->OnClicked.AddDynamic(this, &UGraphicSettingWidget::OnFullScreenLeftClicked);	
	FullScreenRight->OnClicked.AddDynamic(this, &UGraphicSettingWidget::OnFullScreenRightClicked);
	ResolutionDown->OnClicked.AddDynamic(this, &UGraphicSettingWidget::OnResolutionDownClicked);
	ResolutionUp->OnClicked.AddDynamic(this, &UGraphicSettingWidget::OnResolutionUpClicked);
	ReturnButton->OnClicked.AddDynamic(this, &UGraphicSettingWidget::CloseWidget);
	ApplyButton->OnClicked.AddDynamic(this, &UGraphicSettingWidget::OnApplyButtonClicked);
}

void UGraphicSettingWidget::SetResolutionIndex(FIntPoint resolution)
{
	switch (resolution.X)
	{
		case 1280:
			CurrentResolutionIndex = 0;
			break;
		case 1600:
			CurrentResolutionIndex = 1;
			break;
		case 1920:
			CurrentResolutionIndex = 2;
			break;
	}
}

void UGraphicSettingWidget::SetResolution(int32 resolutionIndex)
{
	switch (resolutionIndex)
	{
		case 0:
			CurrentResolutions = FIntPoint(1280, 720);
			break;
		case 1:
			CurrentResolutions = FIntPoint(1600, 900);
			break;
		case 2:
			CurrentResolutions = FIntPoint(1920, 1080);
			break;
	}

}

void UGraphicSettingWidget::OnFullScreenRightClicked()
{
	auto windowMode = CurrentWindowMode.GetValue();
	switch (windowMode)
	{
		case EWindowMode::Fullscreen:
			CurrentWindowMode = EWindowMode::WindowedFullscreen;
			break;
		case EWindowMode::WindowedFullscreen:
			CurrentWindowMode = EWindowMode::Windowed;
			break;
		case EWindowMode::Windowed:
			CurrentWindowMode = EWindowMode::Fullscreen;
			break;
	}
}

void UGraphicSettingWidget::OnFullScreenLeftClicked()
{
	auto windowMode = CurrentWindowMode.GetValue();
	switch (windowMode)
	{
	case EWindowMode::Fullscreen:
		CurrentWindowMode = EWindowMode::Windowed;
		break;
	case EWindowMode::WindowedFullscreen:
		CurrentWindowMode = EWindowMode::Fullscreen;
		break;
	case EWindowMode::Windowed:
		CurrentWindowMode = EWindowMode::WindowedFullscreen;
		break;
	}
}

void UGraphicSettingWidget::OnResolutionUpClicked()
{
	switch(CurrentResolutionIndex)
	{
		case 0:
			CurrentResolutionIndex = 1;
			SetResolution(CurrentResolutionIndex);
			break;
		case 1:
			CurrentResolutionIndex = 2;
			SetResolution(CurrentResolutionIndex);
			break;
		case 2:
			CurrentResolutionIndex = 0;
			SetResolution(CurrentResolutionIndex);
			break;
	}
}

void UGraphicSettingWidget::OnResolutionDownClicked()
{
	switch (CurrentResolutionIndex)
	{
	case 0:
		CurrentResolutionIndex = 2;
		SetResolution(CurrentResolutionIndex);
		break;
	case 1:
		CurrentResolutionIndex = 0;
		SetResolution(CurrentResolutionIndex);
		break;
	case 2:
		CurrentResolutionIndex = 1;
		SetResolution(CurrentResolutionIndex);
		break;
	}
}

void UGraphicSettingWidget::OnApplyButtonClicked()
{
	auto gameSettig = GEngine->GetGameUserSettings();
	gameSettig->SetFullscreenMode(CurrentWindowMode.GetValue());
	gameSettig->SetScreenResolution(CurrentResolutions);
	gameSettig->ApplySettings(false);

	//if (CurrentWindowMode.GetValue() == EWindowMode::Windowed)
	//{
	//	GEngine->GameViewport->GetWindow()->SetWindowMode(EWindowMode::Windowed);
	//}
}

void UGraphicSettingWidget::Init()
{
	Super::Init();
}

void UGraphicSettingWidget::CloseWidget()
{
	Super::CloseWidget();
}
