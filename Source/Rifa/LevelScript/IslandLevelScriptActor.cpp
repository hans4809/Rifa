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
#include "Sound/AmbientSound.h"
#include "Components/AudioComponent.h"

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
				FirstLevelSequenceActor->SequencePlayer->Play();
				RifaGameInstanceReference->LevelSequencePlayerArr[0] = true;
				FirstLevelSequenceActor->SequencePlayer->OnFinished.AddDynamic(this, &AIslandLevelScriptActor::OnFinishedFirstLevelSequence);
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
	if (IsValid(BGMActor))
	{
		if (IsValid(RifaGameInstanceReference))
		{
			for (int i = 0; i < RifaGameInstanceReference->SoundItemOnOffMap.Num(); i++)
			{
				FName InstParam = FName(FString::Printf(TEXT("Inst%d"), i));
				FName BGMParam = FName(FString::Printf(TEXT("BGMIndex")));
				BGMActor->GetAudioComponent()->SetIntParameter(BGMParam, RifaGameInstanceReference->BGMIndex);
				if (RifaGameInstanceReference->SoundItemHavingMap[EItem(i)])
				{
					if (RifaGameInstanceReference->SoundItemOnOffMap[EItem(i)])
						BGMActor->GetAudioComponent()->SetFloatParameter(InstParam, 1.f);
					else
						BGMActor->GetAudioComponent()->SetFloatParameter(InstParam, 0.f);
				}
				else
					BGMActor->GetAudioComponent()->SetFloatParameter(InstParam, 0.f);
			}
		}
		BGMActor->Play();
	}
	
}

void AIslandLevelScriptActor::OnFinishedFirstLevelSequence()
{
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
