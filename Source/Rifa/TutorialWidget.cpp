// Fill out your copyright notice in the Description page of Project Settings.


#include "TutorialWidget.h"
#include "Components/Image.h"
#include "Engine/Texture2D.h"
#include "Components/PanelSlot.h"
#include <Kismet/GameplayStatics.h>
#include "MyGameInstance.h"
#include "IslandLevelScriptActor.h"

void UTutorialWidget::NativeConstruct()
{
	Super::NativeConstruct();
	TutorialImage = Cast<UImage>(GetWidgetFromName(TEXT("TutorialImage")));
	RifaGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	IslandLevelScriptActor = Cast<AIslandLevelScriptActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AIslandLevelScriptActor::StaticClass()));

	const UEnum* TutorialTypeName = FindObject<UEnum>(nullptr, TEXT("/Script/Rifa.ETutorialType"));
	if (TutorialTypeName)
	{
		FString EnumMetaData = TutorialTypeName->GetDisplayNameTextByValue((int64)ThisTutorialType).ToString();
		FString TutorialTexturePath = FString::Printf(TEXT("/Script/Engine.Texture2D'/Game/UIPNG/Tutorial/Tutorial-%s.Tutorial-%s'"), *EnumMetaData, *EnumMetaData);
		UTexture2D* TutorialTexture = LoadObject<UTexture2D>(NULL, *TutorialTexturePath, NULL, LOAD_None, NULL);
		if (IsValid(TutorialTexture))
		{
			TutorialImage->SetBrushFromTexture(TutorialTexture);
			TutorialImage->SetBrushSize(FVector2D(TutorialTexture->GetSizeX(), TutorialTexture->GetSizeY()));
		}
	}
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
	FString TutorialTexturePath;
	UTexture2D* TutorialTexture = nullptr;
	FTimerHandle TutorialTimer;
	switch (ThisTutorialType)
	{
	case ETutorialType::Movement:
		ThisTutorialType = ETutorialType::Jump;
		TutorialTexturePath = FString::Printf(TEXT("/Script/Engine.Texture2D'/Game/UIPNG/Tutorial/Tutorial-Jump.Tutorial-Jump'"));
		TutorialTexture = LoadObject<UTexture2D>(NULL, *TutorialTexturePath, NULL, LOAD_None, NULL);
		if (IsValid(TutorialTexture))
		{
			TutorialImage->SetBrushFromTexture(TutorialTexture);
			TutorialImage->SetDesiredSizeOverride(FVector2D(TutorialTexture->GetSizeX(), TutorialTexture->GetSizeY()));
		}
		GetWorld()->GetTimerManager().SetTimer(TutorialTimer, this, &UTutorialWidget::ChangeImage, 5.0f, false);
		break;
	case ETutorialType::Jump:
		ThisTutorialType = ETutorialType::Dash;
		TutorialTexturePath = FString::Printf(TEXT("/Script/Engine.Texture2D'/Game/UIPNG/Tutorial/Tutorial-Dash.Tutorial-Dash'"));
		TutorialTexture = LoadObject<UTexture2D>(NULL, *TutorialTexturePath, NULL, LOAD_None, NULL);
		if (IsValid(TutorialTexture))
		{
			TutorialImage->SetBrushFromTexture(TutorialTexture);
			TutorialImage->SetDesiredSizeOverride(FVector2D(TutorialTexture->GetSizeX(), TutorialTexture->GetSizeY()));
		}
		GetWorld()->GetTimerManager().SetTimer(TutorialTimer, this, &UTutorialWidget::ChangeImage, 5.0f, false);
		break;
	default:
		CloseWidget();
		break;
	}
}