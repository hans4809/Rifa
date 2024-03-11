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
				CharacterReference->SetActorLocation(RifaGameInstanceReference->SavePosition);
			}
		}
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
