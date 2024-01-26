// Fill out your copyright notice in the Description page of Project Settings.


#include "IslandLevelScriptActor.h"
#include "MyGameInstance.h"
#include "RifaCharacter.h"
#include "LevelSequence/Public/LevelSequence.h"
#include "LevelSequence/Public/LevelSequencePlayer.h"
#include "LevelSequence/Public/LevelSequenceActor.h"
#include <Kismet/GameplayStatics.h>
#include "LevelSequenceCharacterActor.h"
#include "GameHUD.h"
#include "RifaHUD.h"

void AIslandLevelScriptActor::BeginPlay()
{
	Super::BeginPlay();
	RifaGameInstanceReference = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	CharacterReference = Cast<ARifaCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (RifaGameInstanceReference->LevelSequencePlayerArr[0]) 
	{
		/*CharacterReference->DisableInput(Cast<APlayerController>(CharacterReference->Controller));
		CharacterReference->SetActorHiddenInGame(true);*/
		if (IsValid(FirstLevelSequenceActor)) 
		{
			FirstLevelSequenceActor->SequencePlayer->Play();
			GetWorld()->GetTimerManager().SetTimer(SequenceTimer, this, &AIslandLevelScriptActor::OnFinishedFirstLevelSequence, FirstLevelSequenceActor->SequencePlayer->GetDuration().AsSeconds(),false);
		}
	}
	else
	{
		if (IsValid(FirstLevelSequenceCharacterActor))
		{
			FirstLevelSequenceCharacterActor->Destroy();
		}
		if (IsValid(RifaHUDClass))
		{
			//RifaHUD = Cast<ARifaHUD>(Cast<APlayerController>(Controller)->GetHUD());
		}
		if (IsValid(GameHUDWidgetClass))
		{
			GameHUDWidget = Cast<UGameHUD>(CreateWidget(GetWorld(), GameHUDWidgetClass));
			if (IsValid(GameHUDWidget))
			{
				GameHUDWidget->Init();
			}
		}
	}

}

void AIslandLevelScriptActor::OnFinishedFirstLevelSequence()
{
	if (IsValid(SecondLevelSequenceActor)) 
	{
		SecondLevelSequenceActor->SequencePlayer->Play();
		GetWorld()->GetTimerManager().SetTimer(SequenceTimer, this, &AIslandLevelScriptActor::OnFinishedSecondLevelSequence, SecondLevelSequenceActor->SequencePlayer->GetDuration().AsSeconds(), false);
	}
}

void AIslandLevelScriptActor::OnFinishedSecondLevelSequence()
{
	RifaGameInstanceReference->LevelSequencePlayerArr[0] = false;
	if (IsValid(FirstLevelSequenceCharacterActor))
	{
		FirstLevelSequenceCharacterActor->Destroy();
	}
}