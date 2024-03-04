// Fill out your copyright notice in the Description page of Project Settings.


#include "IslandLevelScriptActor.h"
#include "Data/MyGameInstance.h"
#include "Character/RifaCharacter.h"
#include "LevelSequence/Public/LevelSequence.h"
#include "LevelSequence/Public/LevelSequencePlayer.h"
#include "LevelSequence/Public/LevelSequenceActor.h"
#include <Kismet/GameplayStatics.h>
#include "Widget/GameHUD.h"
#include "Widget/TutorialWidget.h"

AIslandLevelScriptActor::AIslandLevelScriptActor()
{

}

void AIslandLevelScriptActor::BeginPlay()
{
	Super::BeginPlay();

	if (RifaGameInstanceReference) 
	{
		if (!RifaGameInstanceReference->LevelSequencePlayerArr[0])
		{
			if (IsValid(FirstLevelSequenceActor))
			{
				FTimerHandle SequenceTimer;
				if (GameHUDWidgetAsset)
				{
					GameHUDWidgetAsset->CloseWidget();
				}
				FirstLevelSequenceActor->SequencePlayer->Play();
				GetWorld()->GetTimerManager().SetTimer(SequenceTimer, this, &AIslandLevelScriptActor::OnFinishedFirstLevelSequence, FirstLevelSequenceActor->SequencePlayer->GetDuration().AsSeconds(), false);
			}
		}
		if (CharacterReference) 
		{
			if (RifaGameInstanceReference->SavePosition != FVector::ZeroVector)
			{
				CharacterReference->SetActorLocation(RifaGameInstanceReference->SavePosition);
			}
		}
	}
	
}

void AIslandLevelScriptActor::OnFinishedFirstLevelSequence()
{
	RifaGameInstanceReference->LevelSequencePlayerArr[0] = true;
	if (IsValid(GameHUDWidgetClass))
	{
		GameHUDWidgetAsset = Cast<UGameHUD>(CreateWidget(GetWorld(), GameHUDWidgetClass));
		if (IsValid(GameHUDWidgetAsset))
		{
			GameHUDWidgetAsset->Init();
		}
	}
	if (!RifaGameInstanceReference->IsTutorialFinishedMap[ETutorialType::Movement])
	{
		if (IsValid(TutorialWidgetClass))
		{
			TutorialWidgetAsset = Cast<UTutorialWidget>(CreateWidget(GetWorld(), TutorialWidgetClass));
			if (IsValid(TutorialWidgetAsset))
			{
				TutorialWidgetAsset->ThisTutorialType = ETutorialType::Movement;
				TutorialWidgetAsset->Init();
			}
		}
	}
}

void AIslandLevelScriptActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
