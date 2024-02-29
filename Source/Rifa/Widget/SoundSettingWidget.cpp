// Fill out your copyright notice in the Description page of Project Settings.


#include "SoundSettingWidget.h"
#include "Components/Button.h"
#include <Kismet/GameplayStatics.h>
#include "Sound/BGMSoundActor.h"
#include "Components/AudioComponent.h"
#include "CollectionWidget.h"
#include "Components/Slider.h"
#include "Sound/SoundClass.h"
#include "Sound/SoundMix.h"
#include "Data/MyGameInstance.h"

void USoundSettingWidget::NativeConstruct()
{
	Super::NativeConstruct();
	CollectionButton = Cast<UButton>(GetWidgetFromName(TEXT("CollectionButton")));
	ReturnButton = Cast<UButton>(GetWidgetFromName(TEXT("ReturnButton")));
	BGMSlider = Cast<USlider>(GetWidgetFromName(TEXT("BGMSlider")));
	EnviromentalSlider = Cast<USlider>(GetWidgetFromName(TEXT("EnviromentalSlider")));
	SFXSlider = Cast<USlider>(GetWidgetFromName(TEXT("SFXSlider")));

	CollectionButton->OnClicked.AddDynamic(this, &USoundSettingWidget::CollectionButtonClicked);
	ReturnButton->OnClicked.AddDynamic(this, &USoundSettingWidget::CloseWidget);
	BGMSlider->OnValueChanged.AddDynamic(this, &USoundSettingWidget::BGMSliderValueChanged);
	EnviromentalSlider->OnValueChanged.AddDynamic(this, &USoundSettingWidget::EnviromentalSliderValueChanged);
	SFXSlider->OnValueChanged.AddDynamic(this, &USoundSettingWidget::SFXSliderValueChanged);

	BGMComponent = Cast<UAudioComponent>(UGameplayStatics::GetActorOfClass(GetWorld(), ABGMSoundActor::StaticClass()));
	RifaGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	BGMSlider->SetValue(RifaGameInstance->BGMVolume);
	EnviromentalSlider->SetValue(RifaGameInstance->EnviromentalVolume);
	SFXSlider->SetValue(RifaGameInstance->SFXVolume);
}

void USoundSettingWidget::Init()
{
	Super::Init();
}

void USoundSettingWidget::CloseWidget()
{
	Super::CloseWidget();
}

void USoundSettingWidget::CrossFadeSound()
{
	AudioParam += 0.4f;
	if (BGMComponent == nullptr)
		return;
	BGMComponent->SetFloatParameter(TEXT("BGM_6"), AudioParam);
}

void USoundSettingWidget::CollectionButtonClicked()
{
	if (IsValid(CollectionWidgetClass)) 
	{
		CollectionWidgetAsset = Cast<UCollectionWidget>(CreateWidget(GetWorld(), CollectionWidgetClass));
		CollectionWidgetAsset->Init();
	}
}

void USoundSettingWidget::BGMSliderValueChanged(float Value)
{
	if (IsValid(BGMClass) && IsValid(BGMClassMix)) 
	{
		UGameplayStatics::SetSoundMixClassOverride(GetWorld(), BGMClassMix, BGMClass, Value, 1.f, 0.f);
		UGameplayStatics::PushSoundMixModifier(GetWorld(), BGMClassMix);
		RifaGameInstance->BGMVolume = Value;
	}
}

void USoundSettingWidget::EnviromentalSliderValueChanged(float Value)
{
	if (IsValid(EnviromentalClass) && IsValid(EnviromentalClassMix)) 
	{
		UGameplayStatics::SetSoundMixClassOverride(GetWorld(), EnviromentalClassMix, EnviromentalClass, Value, 1.f, 0.f);
		UGameplayStatics::PushSoundMixModifier(GetWorld(), EnviromentalClassMix);
		RifaGameInstance->EnviromentalVolume = Value;
	}
}

void USoundSettingWidget::SFXSliderValueChanged(float Value)
{
	if (IsValid(SFXClass) && IsValid(SFXClassMix)) 
	{
		UGameplayStatics::SetSoundMixClassOverride(GetWorld(), SFXClassMix, SFXClass, Value, 1.f, 0.f);
		UGameplayStatics::PushSoundMixModifier(GetWorld(), SFXClassMix);
		RifaGameInstance->SFXVolume = Value;
	}
}
