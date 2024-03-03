// Fill out your copyright notice in the Description page of Project Settings.


#include "FieldLevelScriptActor.h"
#include "Data/MyGameInstance.h"
#include "Character/RifaCharacter.h"
#include "LevelSequence/Public/LevelSequence.h"
#include "LevelSequence/Public/LevelSequencePlayer.h"
#include "LevelSequence/Public/LevelSequenceActor.h"
#include <Kismet/GameplayStatics.h>
#include "Widget/GameHUD.h"
#include "Widget/TutorialWidget.h"

AFieldLevelScriptActor::AFieldLevelScriptActor()
{
}

void AFieldLevelScriptActor::BeginPlay()
{
	Super::BeginPlay();
	if (!RifaGameInstanceReference->LevelSequencePlayerArr[4])
	{
		if (IsValid(LevelSequenceActor))
		{
			FTimerHandle SequenceTimer;
			if (GameHUDWidgetAsset)
			{
				GameHUDWidgetAsset->CloseWidget();
			}
			LevelSequenceActor->SequencePlayer->Play();
			GetWorld()->GetTimerManager().SetTimer(SequenceTimer, this, &AFieldLevelScriptActor::OnFinishedLevelSequence, LevelSequenceActor->SequencePlayer->GetDuration().AsSeconds(), false);
		}
	}
}

void AFieldLevelScriptActor::OnFinishedLevelSequence()
{
	RifaGameInstanceReference->LevelSequencePlayerArr[4] = true;
	if (IsValid(GameHUDWidgetClass))
	{
		GameHUDWidgetAsset = Cast<UGameHUD>(CreateWidget(GetWorld(), GameHUDWidgetClass));
		if (IsValid(GameHUDWidgetAsset))
		{
			GameHUDWidgetAsset->Init();
		}
	}
}
