// Fill out your copyright notice in the Description page of Project Settings.


#include "FieldLevelScriptActor.h"
#include "MyGameInstance.h"
#include "RifaCharacter.h"
#include "LevelSequence/Public/LevelSequence.h"
#include "LevelSequence/Public/LevelSequencePlayer.h"
#include "LevelSequence/Public/LevelSequenceActor.h"
#include <Kismet/GameplayStatics.h>
#include "GameHUD.h"
#include "TutorialWidget.h"

AFieldLevelScriptActor::AFieldLevelScriptActor()
{
}

void AFieldLevelScriptActor::BeginPlay()
{
	Super::BeginPlay();
	if (!RifaGameInstanceReference->LevelSequencePlayerArr[3])
	{
		if (IsValid(LevelSequenceActor))
		{
			FTimerHandle SequenceTimer;
			LevelSequenceActor->SequencePlayer->Play();
			GetWorld()->GetTimerManager().SetTimer(SequenceTimer, this, &AFieldLevelScriptActor::OnFinishedLevelSequence, LevelSequenceActor->SequencePlayer->GetDuration().AsSeconds(), false);
		}
	}
	else
	{
		if (IsValid(GameHUDWidgetClass))
		{
			GameHUDWidgetAsset = Cast<UGameHUD>(CreateWidget(GetWorld(), GameHUDWidgetClass));
			if (IsValid(GameHUDWidgetAsset))
			{
				GameHUDWidgetAsset->Init();
			}
		}
	}

}

void AFieldLevelScriptActor::OnFinishedLevelSequence()
{
	RifaGameInstanceReference->LevelSequencePlayerArr[3] = true;
	if (IsValid(GameHUDWidgetClass))
	{
		GameHUDWidgetAsset = Cast<UGameHUD>(CreateWidget(GetWorld(), GameHUDWidgetClass));
		if (IsValid(GameHUDWidgetAsset))
		{
			GameHUDWidgetAsset->Init();
		}
	}
}
