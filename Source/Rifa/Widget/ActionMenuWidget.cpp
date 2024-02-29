// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionMenuWidget.h"
#include "Components/Button.h"
#include "Data/MyGameInstance.h"
#include <Kismet/GameplayStatics.h>
#include "Character/RifaCharacter.h"
#include "Sound/BGMAudioComponent.h"

void UActionMenuWidget::NativeConstruct()
{
	OnButton = Cast<UButton>(GetWidgetFromName(TEXT("OnButton")));
	OffButton = Cast<UButton>(GetWidgetFromName(TEXT("OffButton")));
	CancelButton = Cast<UButton>(GetWidgetFromName(TEXT("CancelButton")));

	OnButton->OnClicked.AddDynamic(this, &UActionMenuWidget::BGMOnButtonClicked);
	OffButton->OnClicked.AddDynamic(this, &UActionMenuWidget::BGMOffButtonClicked);
	CancelButton->OnClicked.AddDynamic(this, &UActionMenuWidget::CancelButtonClicked);

	RifaGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
}

void UActionMenuWidget::BGMOnButtonClicked()
{
	RifaGameInstance->SoundItemOnOffMap[Item(InventorySlot)] = true;
	Cast<ARifaCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->Bgm->BgmRefresh();
}

void UActionMenuWidget::BGMOffButtonClicked()
{
	RifaGameInstance->SoundItemOnOffMap[Item(InventorySlot)] = false;
	Cast<ARifaCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))->Bgm->BgmRefresh();
}

void UActionMenuWidget::CancelButtonClicked()
{
	SetVisibility(ESlateVisibility::Hidden);
}

