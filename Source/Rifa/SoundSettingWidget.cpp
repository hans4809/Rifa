// Fill out your copyright notice in the Description page of Project Settings.


#include "SoundSettingWidget.h"
#include "Components/Button.h"
#include "SoundManagerInstance.h"
#include <Kismet/GameplayStatics.h>
#include "BGMSoundActor.h"
#include "Components/AudioComponent.h"

void USoundSettingWidget::NativeConstruct()
{
	Super::NativeConstruct();
	CollectionButton = Cast<UButton>(GetWidgetFromName(TEXT("CollectionButton")));
	CollectionButton->OnClicked.AddDynamic(this, &USoundSettingWidget::CrossFadeSound);
	BGMComponent = Cast<UAudioComponent>(UGameplayStatics::GetActorOfClass(GetWorld(), ABGMSoundActor::StaticClass()));
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
