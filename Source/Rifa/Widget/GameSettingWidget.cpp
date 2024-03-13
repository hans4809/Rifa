// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSettingWidget.h"
#include "Components/Button.h"
#include "SoundSettingWidget.h"
#include "InputSettingWidget.h"
#include "GraphicSettingWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Character/RifaCharacter.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include <LevelScript/IslandLevelScriptActor.h>
#include "Widget/GameHUD.h"
#include "LevelScript/BaseLevelScriptActor.h"
#include "Sound/AmbientSound.h"
#include "Components/AudioComponent.h"
#include "Character/RifaCharacter.h"

void UGameSettingWidget::NativeConstruct()
{
	Super::NativeConstruct();
	SoundButton = Cast<UButton>(GetWidgetFromName(TEXT("SoundButton")));
	GraphicButton = Cast<UButton>(GetWidgetFromName(TEXT("GraphicButton")));
	ControlButton = Cast<UButton>(GetWidgetFromName(TEXT("ControlButton")));
	ReturnButton = Cast<UButton>(GetWidgetFromName(TEXT("ReturnButton")));
	MainButton = Cast<UButton>(GetWidgetFromName(TEXT("MainButton")));

	ReturnButton->OnClicked.AddDynamic(this, &UGameSettingWidget::ReturnButtonClicked);
	SoundButton->OnClicked.AddDynamic(this, &UGameSettingWidget::SoundButtonClicked);
	GraphicButton->OnClicked.AddDynamic(this, &UGameSettingWidget::GraphicButtonClicked);
	ControlButton->OnClicked.AddDynamic(this, &UGameSettingWidget::InputButtonClicked);
	MainButton->OnClicked.AddDynamic(this, &UGameSettingWidget::MainButtonClicked);

	if (IsValid(CurrentLevelScriptActor)) 
	{
		if (IsValid(CurrentLevelScriptActor->BGMActor))
		{
			//CurrentLevelScriptActor->BGM->Stop();
			CurrentLevelScriptActor->BGMActor->GetAudioComponent()->SetPaused(true);
		}
	}
}

void UGameSettingWidget::Init()
{
	Super::Init();
	APlayerController* Controller = Cast<APlayerController>(Cast<ARifaCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->GetController());
	Controller->SetInputMode(FInputModeUIOnly());
	Controller->bShowMouseCursor = true;
}

void UGameSettingWidget::CloseWidget()
{
	Super::CloseWidget();
	if (IsValid(CurrentLevelScriptActor))
	{
		if (IsValid(CurrentLevelScriptActor->BGMActor))
		{
			CurrentLevelScriptActor->BGMActor->GetAudioComponent()->SetPaused(false);
		}
	}
}

void UGameSettingWidget::ReturnButtonClicked()
{
	APlayerController* Controller = Cast<APlayerController>(Cast<ARifaCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->GetController());
	Controller->SetInputMode(FInputModeGameOnly());
	Controller->bShowMouseCursor = false;
	UWidgetLayoutLibrary::RemoveAllWidgets(GetWorld());
	if (IsValid(CurrentLevelScriptActor))
	{
		if (IsValid(CurrentLevelScriptActor->GameHUDWidgetAsset))
		{
			CurrentLevelScriptActor->GameHUDWidgetAsset->Init();
		}
		if (IsValid(CurrentLevelScriptActor->BGMActor))
		{
			CurrentLevelScriptActor->BGMActor->GetAudioComponent()->SetPaused(false);
		}
	}
	if (ARifaCharacter* Character = Cast<ARifaCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
	{
		Character->CustomTimeDilation = 1.f;
	}
}

void UGameSettingWidget::SoundButtonClicked()
{
	if (IsValid(SoundSettingWidgetClass))
	{
		SoundSettingWidgetAsset = Cast<USoundSettingWidget>(CreateWidget(GetWorld(), SoundSettingWidgetClass));
		SoundSettingWidgetAsset->Init();
	}
}

void UGameSettingWidget::GraphicButtonClicked()
{
	if (IsValid(GraphicSettingWidgetClass))
	{
		GraphicSettingWidgetAsset = Cast<UGraphicSettingWidget>(CreateWidget(GetWorld(), GraphicSettingWidgetClass));
		GraphicSettingWidgetAsset->Init();
	}
}

void UGameSettingWidget::InputButtonClicked()
{
	if (IsValid(InputSettingWidgetClass))
	{
		InputSettingWidgetAsset = Cast<UInputSettingWidget>(CreateWidget(GetWorld(), InputSettingWidgetClass));
		InputSettingWidgetAsset->Init();
	}
}


void UGameSettingWidget::MainButtonClicked()
{
	UGameplayStatics::OpenLevel(this, TEXT("MainMenu"));
}
