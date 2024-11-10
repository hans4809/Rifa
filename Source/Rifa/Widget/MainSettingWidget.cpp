// Fill out your copyright notice in the Description page of Project Settings.


#include "MainSettingWidget.h"
#include "Components/Button.h"
#include "SoundSettingWidget.h"
#include "InputSettingWidget.h"
#include "GraphicSettingWidget.h"
#include "Kismet/GameplayStatics.h"
#include "LevelScript/BaseLevelScriptActor.h"
#include "Sound/AmbientSound.h"
#include "Components/AudioComponent.h"
#include "Data/MyGameInstance.h"

void UMainSettingWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	SoundButton = Cast<UButton>(GetWidgetFromName(TEXT("SoundButton")));
	GraphicButton = Cast<UButton>(GetWidgetFromName(TEXT("GraphicButton")));
	ControlButton = Cast<UButton>(GetWidgetFromName(TEXT("ControlButton")));
	ReturnButton = Cast<UButton>(GetWidgetFromName(TEXT("ReturnButton")));


	if(SoundButton->OnClicked.IsBound())
	{
		SoundButton->OnClicked.Clear();
	}

	if(GraphicButton->OnClicked.IsBound())
	{
		GraphicButton->OnClicked.Clear();
	}

	if(ControlButton->OnClicked.IsBound())
	{
		ControlButton->OnClicked.Clear();
	}

	if (ReturnButton->OnClicked.IsBound())
	{
		ReturnButton->OnClicked.Clear();
	}

	ReturnButton->OnClicked.AddDynamic(this, &UMainSettingWidget::CloseWidget);
	SoundButton->OnClicked.AddDynamic(this, &UMainSettingWidget::SoundButtonClicked);
	GraphicButton->OnClicked.AddDynamic(this, &UMainSettingWidget::GraphicButtonClicked);
	ControlButton->OnClicked.AddDynamic(this, &UMainSettingWidget::InputButtonClicked);

	CurrentLevelScriptActor = Cast<ABaseLevelScriptActor>(GetWorld()->GetLevelScriptActor());
	if (IsValid(CurrentLevelScriptActor))
	{
		if (IsValid(CurrentLevelScriptActor->BGMActor))
		{
			//CurrentLevelScriptActor->BGM->Stop();
			CurrentLevelScriptActor->BGMActor->GetAudioComponent()->SetPaused(true);
		}
	}
}

void UMainSettingWidget::Init()
{
	Super::Init();
}

void UMainSettingWidget::CloseWidget()
{
	Super::CloseWidget();
	if (IsValid(CurrentLevelScriptActor))
	{
		if (IsValid(CurrentLevelScriptActor->BGMActor))
		{
			CurrentLevelScriptActor->BGMActor->GetAudioComponent()->SetPaused(false);
		}
	}
	//UGameplayStatics::SetGamePaused(GetWorld(), false);
}

void UMainSettingWidget::SoundButtonClicked()
{
	if (IsValid(SoundSettingWidgetClass)&& !IsValid(SoundSettingWidgetAsset))
	{
		SoundSettingWidgetAsset = Cast<USoundSettingWidget>(CreateWidget(GetWorld(), SoundSettingWidgetClass));
	}

	if (IsValid(SoundSettingWidgetAsset))
	{
		SoundSettingWidgetAsset->ParentWidget = this;
		SoundSettingWidgetAsset->Init();
	}

}

void UMainSettingWidget::GraphicButtonClicked()
{
	if (IsValid(GraphicSettingWidgetClass)&& !IsValid(GraphicSettingWidgetAsset))
	{
		GraphicSettingWidgetAsset = Cast<UGraphicSettingWidget>(CreateWidget(GetWorld(), GraphicSettingWidgetClass));
	}

	if (IsValid(GraphicSettingWidgetAsset))
	{
		GraphicSettingWidgetAsset->ParentWidget = this;
		GraphicSettingWidgetAsset->Init();
	}

}

void UMainSettingWidget::InputButtonClicked()
{
	if (IsValid(InputSettingWidgetClass) && !IsValid(InputSettingWidgetAsset))
	{
		InputSettingWidgetAsset = Cast<UInputSettingWidget>(CreateWidget(GetWorld(), InputSettingWidgetClass));
	}

	if(IsValid(InputSettingWidgetAsset))
	{
		InputSettingWidgetAsset->ParentWidget = this;
		InputSettingWidgetAsset->Init();
	}
}
