// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionMenuWidget.h"
#include "Components/Button.h"
#include "Data/MyGameInstance.h"
#include <Kismet/GameplayStatics.h>
#include "Character/RifaCharacter.h"
#include "Sound/BGMAudioComponent.h"
#include "Components/AudioComponent.h"

void UActionMenuWidget::NativeConstruct()
{
	OnButton = Cast<UButton>(GetWidgetFromName(TEXT("OnButton")));
	CancelButton = Cast<UButton>(GetWidgetFromName(TEXT("CancelButton")));

	OnButton->OnClicked.AddDynamic(this, &UActionMenuWidget::BGMOnButtonClicked);
	CancelButton->OnClicked.AddDynamic(this, &UActionMenuWidget::CancelButtonClicked);

	RifaGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	IsOn = RifaGameInstance->SoundItemOnOffMap[EItem(InventorySlot)];
	FString InstSoundPath = FString::Printf(TEXT("/Game/Sounds/SFX/UI_Listen_Collect_%d.UI_Listen_Collect_%d"), InventorySlot, InventorySlot);
	USoundBase* InstAsset = LoadObject<USoundBase>(NULL, *InstSoundPath, NULL, LOAD_None, NULL);
	if (IsValid(InstAsset))
	{
		InstSound = InstAsset;
		InstAudioComponent = UGameplayStatics::CreateSound2D(GetWorld(), InstSound, 0.f, 0.f, 0.f, nullptr, false, false);
	}
}

void UActionMenuWidget::BGMOnButtonClicked()
{
	if (RifaGameInstance) 
	{
		if (RifaGameInstance->SoundItemOnOffMap[EItem(InventorySlot)]) 
		{
			RifaGameInstance->SoundItemOnOffMap[EItem(InventorySlot)] = false;
			IsOn = RifaGameInstance->SoundItemOnOffMap[EItem(InventorySlot)];
			InstAudioComponent->Stop();
			InstSound->DestroyNonNativeProperties();
		}
		else 
		{
			RifaGameInstance->SoundItemOnOffMap[EItem(InventorySlot)] = true;
			IsOn = RifaGameInstance->SoundItemOnOffMap[EItem(InventorySlot)];
			InstAudioComponent->Play();
			if (IsValid(InstSound)) 
			{
				auto Sound = InstAudioComponent->Sound;
				UGameplayStatics::PlaySound2D(GetWorld(), Sound, 1.f, 1.f, 0.f, InstSoundConcurrency, nullptr, false);
			}
			else 
			{
				UGameplayStatics::PlaySound2D(GetWorld(), InstSound, 1.f, 1.f, 0.f, InstSoundConcurrency, nullptr, false);
			}
		}
		if (auto CharacterReference = Cast<ARifaCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))) 
		{
			CharacterReference->Bgm->BgmRefresh();
		}
	}

}

void UActionMenuWidget::BGMOffButtonClicked()
{
	RifaGameInstance->SoundItemOnOffMap[EItem(InventorySlot)] = false;
	Cast<ARifaCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->Bgm->BgmRefresh();
}

void UActionMenuWidget::CancelButtonClicked()
{
	SetVisibility(ESlateVisibility::Hidden);
	InstAudioComponent->Stop();
	InstSound->DestroyNonNativeProperties();
}

