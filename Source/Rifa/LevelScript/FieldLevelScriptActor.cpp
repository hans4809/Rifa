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
				FTimerHandle SequenceTimer;
				if (GameHUDWidgetAsset)
				{
					GameHUDWidgetAsset->CloseWidget();
				}
				LevelSequenceActor->SequencePlayer->Play();
				CharacterReference->DisableInput(Cast<APlayerController>(CharacterReference->Controller));
				GetWorld()->GetTimerManager().SetTimer(SequenceTimer, this, &AFieldLevelScriptActor::OnFinishedLevelSequence, LevelSequenceActor->SequencePlayer->GetDuration().AsSeconds(), false);
			}
		}
		if (CharacterReference) 
		{
			if (RifaGameInstanceReference->SavePosition != FVector::ZeroVector) 
			{
				//CharacterReference->SetActorLocation(RifaGameInstanceReference->SavePosition);
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
		BGMActor->GetAudioComponent()->FadeIn(0.1f);
	}
}

void AFieldLevelScriptActor::OnFinishedLevelSequence()
{
	RifaGameInstanceReference->LevelSequencePlayerArr[4] = true;
	CharacterReference->EnableInput(Cast<APlayerController>(CharacterReference->Controller));
	if (IsValid(GameHUDWidgetClass))
	{
		GameHUDWidgetAsset = Cast<UGameHUD>(CreateWidget(GetWorld(), GameHUDWidgetClass));
		if (IsValid(GameHUDWidgetAsset))
		{
			GameHUDWidgetAsset->Init();
		}
	}
}
