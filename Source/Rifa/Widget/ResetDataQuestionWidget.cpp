// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/ResetDataQuestionWidget.h"
#include "Components/Button.h"
#include <Kismet/GameplayStatics.h>
#include "Data/MyGameInstance.h"

void UResetDataQuestionWidget::NativeConstruct()
{
	Super::NativeConstruct();
	YesButton = Cast<UButton>(GetWidgetFromName(TEXT("YesButton")));
	NoButton = Cast<UButton>(GetWidgetFromName(TEXT("NoButton")));
	YesButton->OnClicked.AddDynamic(this, &UResetDataQuestionWidget::OnYesButtonClicked);
	NoButton->OnClicked.AddDynamic(this, &UResetDataQuestionWidget::OnNoButtonClicked);
}

void UResetDataQuestionWidget::Init()
{
	Super::Init();
}

void UResetDataQuestionWidget::CloseWidget()
{
	Super::CloseWidget();
}

void UResetDataQuestionWidget::OnYesButtonClicked()
{
	auto GameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GameInstance)
	{
		GameInstance->ResetSaveData();
		FName LevelName = GameInstance->CurrentLevelName;
		UGameplayStatics::OpenLevel(this, LevelName);
	}
}

void UResetDataQuestionWidget::OnNoButtonClicked()
{
	CloseWidget();
}

