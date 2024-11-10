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
#include "DialogWidget.h"

void UGameSettingWidget::NativeConstruct()
{
	Super::NativeConstruct();
	SoundButton = Cast<UButton>(GetWidgetFromName(TEXT("SoundButton")));
	GraphicButton = Cast<UButton>(GetWidgetFromName(TEXT("GraphicButton")));
	ControlButton = Cast<UButton>(GetWidgetFromName(TEXT("ControlButton")));
	ReturnButton = Cast<UButton>(GetWidgetFromName(TEXT("ReturnButton")));
	MainButton = Cast<UButton>(GetWidgetFromName(TEXT("MainButton")));

	if(SoundButton->OnClicked.IsBound())
		SoundButton->OnClicked.Clear();
	if (GraphicButton->OnClicked.IsBound())
		GraphicButton->OnClicked.Clear();
	if (ControlButton->OnClicked.IsBound())
		ControlButton->OnClicked.Clear();
	if (ReturnButton->OnClicked.IsBound())
		ReturnButton->OnClicked.Clear();
	if (MainButton->OnClicked.IsBound())
		MainButton->OnClicked.Clear();

	ReturnButton->OnClicked.AddDynamic(this, &UGameSettingWidget::ReturnButtonClicked);
	SoundButton->OnClicked.AddDynamic(this, &UGameSettingWidget::SoundButtonClicked);
	GraphicButton->OnClicked.AddDynamic(this, &UGameSettingWidget::GraphicButtonClicked);
	ControlButton->OnClicked.AddDynamic(this, &UGameSettingWidget::InputButtonClicked);
	MainButton->OnClicked.AddDynamic(this, &UGameSettingWidget::MainButtonClicked);

	if (IsValid(CurrentLevelScriptActor)) 
	{
		if (IsValid(CurrentLevelScriptActor->BGMActor))
		{
			CurrentLevelScriptActor->BGMActor->GetAudioComponent()->SetPaused(true);
		}
	}
}

void UGameSettingWidget::Init()
{
	Super::Init();
}

void UGameSettingWidget::CloseWidget()
{
	Super::CloseWidget();
}

FReply UGameSettingWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	FReply returnReply = Super::NativeOnKeyDown(InGeometry, InKeyEvent);

	if (InKeyEvent.GetKey() == EKeys::Escape)
	{
		if (IsValid(CurrentLevelScriptActor))
		{
			if (IsValid(CurrentLevelScriptActor->BGMActor))
				CurrentLevelScriptActor->BGMActor->GetAudioComponent()->SetPaused(false);
		}

		ARifaCharacter* Character = Cast<ARifaCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		if(IsValid(Character))
			Character->CustomTimeDilation = 1.f;

		APlayerController* Controller = Cast<APlayerController>(Character->GetController());
		if (IsValid(Controller))
		{
			Controller->SetInputMode(FInputModeGameOnly());
			Controller->bShowMouseCursor = false;
		}
	}

	return returnReply;
}

void UGameSettingWidget::ReturnButtonClicked()
{
	CloseWidget();
	if (IsValid(CurrentLevelScriptActor))
	{
		if (IsValid(CurrentLevelScriptActor->BGMActor))
			CurrentLevelScriptActor->BGMActor->GetAudioComponent()->SetPaused(false);
	}

	ARifaCharacter* Character = Cast<ARifaCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (IsValid(Character))
		Character->CustomTimeDilation = 1.f;

	APlayerController* Controller = Cast<APlayerController>(Character->GetController());
	if (IsValid(Controller))
	{
		Controller->SetInputMode(FInputModeGameOnly());
		Controller->bShowMouseCursor = false;
	}
}

void UGameSettingWidget::SoundButtonClicked()
{
	if (IsValid(SoundSettingWidgetClass)&&!IsValid(SoundSettingWidgetAsset))
		SoundSettingWidgetAsset = Cast<USoundSettingWidget>(CreateWidget(GetWorld(), SoundSettingWidgetClass));
	
	if (IsValid(SoundSettingWidgetAsset))
	{
		SoundSettingWidgetAsset->Init();
		SoundSettingWidgetAsset->ParentWidget = this;
	}
}

void UGameSettingWidget::GraphicButtonClicked()
{
	if (IsValid(GraphicSettingWidgetClass) && !IsValid(GraphicSettingWidgetAsset))
		GraphicSettingWidgetAsset = Cast<UGraphicSettingWidget>(CreateWidget(GetWorld(), GraphicSettingWidgetClass));

	if (IsValid(GraphicSettingWidgetAsset))
	{
		GraphicSettingWidgetAsset->Init();
		GraphicSettingWidgetAsset->ParentWidget = this;
	}
}

void UGameSettingWidget::InputButtonClicked()
{
	if (IsValid(InputSettingWidgetClass) && !IsValid(InputSettingWidgetAsset))
		InputSettingWidgetAsset = Cast<UInputSettingWidget>(CreateWidget(GetWorld(), InputSettingWidgetClass));
	
	if (IsValid(InputSettingWidgetAsset))
	{
		InputSettingWidgetAsset->Init();
		InputSettingWidgetAsset->ParentWidget = this;
	}
}


void UGameSettingWidget::MainButtonClicked()
{
	UGameplayStatics::OpenLevel(this, TEXT("MainMenu"));
}