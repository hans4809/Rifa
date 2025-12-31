// Fill out your copyright notice in the Description page of Project Settings.


#include "FieldLevelScriptActor.h"
#include "Data/MyGameInstance.h"
#include "Character/RifaCharacter.h"
#include "LevelSequence.h"
#include "LevelSequencePlayer.h"
#include "LevelSequenceActor.h"
#include <Kismet/GameplayStatics.h>
#include "Widget/GameHUD.h"
#include "Widget/TutorialWidget.h"
#include "Sound/AmbientSound.h"
#include "Components/AudioComponent.h"

AFieldLevelScriptActor::AFieldLevelScriptActor()
{
}

void AFieldLevelScriptActor::BeginPlay()
{
	Super::BeginPlay();

	if (RifaGameInstanceReference) 
	{
		if (!RifaGameInstanceReference->LevelSequencePlayerArr[4])
		{
			if (IsValid(LevelSequenceActor))
			{
				LevelSequenceActor->SequencePlayer->Play();
				RifaGameInstanceReference->LevelSequencePlayerArr[4] = true;
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
				FName Parameter = FName(FString::Printf(TEXT("Inst%d"), i));
				RifaGameInstanceReference->BGMIndex = 1;
				BGMActor->GetAudioComponent()->SetIntParameter(FName(TEXT("BGMIndex")), RifaGameInstanceReference->BGMIndex);
				if (RifaGameInstanceReference->SoundItemHavingMap[EItem(i)])
				{
					if (RifaGameInstanceReference->SoundItemOnOffMap[EItem(i)])
					{
						BGMActor->GetAudioComponent()->SetFloatParameter(Parameter, 1.f);
					}
					else
					{
						BGMActor->GetAudioComponent()->SetFloatParameter(Parameter, 0.f);
					}
				}
				else
				{
					BGMActor->GetAudioComponent()->SetFloatParameter(Parameter, 0.f);
				}
			}
		}
		if (BGMActor->GetAudioComponent()->IsPlaying())
		{
			BGMActor->Stop();
		}
		BGMActor->Play();
	}
}