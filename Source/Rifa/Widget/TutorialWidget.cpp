// Fill out your copyright notice in the Description page of Project Settings.


#include "TutorialWidget.h"
#include "Components/Image.h"
#include "Engine/Texture2D.h"
#include "Components/PanelSlot.h"
#include <Kismet/GameplayStatics.h>
#include "Data/MyGameInstance.h"
#include "LevelScript/IslandLevelScriptActor.h"

void UTutorialWidget::NativeConstruct()
{
	Super::NativeConstruct();
	WASDImage = Cast<UImage>(GetWidgetFromName(TEXT("WASDImage")));
	JumpImage = Cast<UImage>(GetWidgetFromName(TEXT("JumpImage")));
	DashImage = Cast<UImage>(GetWidgetFromName(TEXT("DashImage")));

	JumpImage->SetVisibility(ESlateVisibility::Hidden);
	DashImage->SetVisibility(ESlateVisibility::Hidden);

	RifaGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
}

void UTutorialWidget::Init()
{
	Super::Init();
	RifaGameInstance->IsTutorialFinishedMap[ThisTutorialType] = true;
	FTimerHandle TutorialTimer;
	GetWorld()->GetTimerManager().SetTimer(TutorialTimer, this, &UTutorialWidget::ChangeImage, 5.0f, false);
}

void UTutorialWidget::CloseWidget()
{
	Super::CloseWidget();
}

void UTutorialWidget::ChangeImage()
{
	FTimerHandle TutorialTimer;
	switch (ThisTutorialType)
	{
	case ETutorialType::Movement:
		ThisTutorialType = ETutorialType::Jump;
		WASDImage->SetVisibility(ESlateVisibility::Hidden);
		JumpImage->SetVisibility(ESlateVisibility::Visible);
		DashImage->SetVisibility(ESlateVisibility::Hidden);
		GetWorld()->GetTimerManager().SetTimer(TutorialTimer, this, &UTutorialWidget::ChangeImage, 5.0f, false);
		break;
	case ETutorialType::Jump:
		ThisTutorialType = ETutorialType::Dash;
		WASDImage->SetVisibility(ESlateVisibility::Hidden);
		JumpImage->SetVisibility(ESlateVisibility::Hidden);
		DashImage->SetVisibility(ESlateVisibility::Visible);
		GetWorld()->GetTimerManager().SetTimer(TutorialTimer, this, &UTutorialWidget::ChangeImage, 5.0f, false);
		break;
	default:
		CloseWidget();
		break;
	}
}