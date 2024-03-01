// Fill out your copyright notice in the Description page of Project Settings.


#include "SoundItem.h"
#include "NiagaraComponent.h"
#include "Data/MyGameInstance.h"
#include "Widget/PickupText.h"
#include <Kismet/GameplayStatics.h>
#include "Character/RifaCharacter.h"
#include "LevelSequence/Public/LevelSequence.h"
#include "LevelSequence/Public/LevelSequencePlayer.h"
#include "LevelSequence/Public/LevelSequenceActor.h"

ASoundItem::ASoundItem()
{
	Particle = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Particle"));
	Particle->SetupAttachment(RootComponent);
	
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> PARTICLE(TEXT("/Script/Niagara.NiagaraSystem'/Game/VFX/VFX_item.VFX_item'"));
	if (PARTICLE.Succeeded()) 
	{
		Particle->SetAsset(PARTICLE.Object);
	}
}

void ASoundItem::BeginPlay()
{
	Super::BeginPlay();
	if (RifaGameInstance->SoundItemHavingMap[(EItem)ThisSoundItemIndex])
	{
		Destroy();
		return;
	}
	else
	{
		if (IsValid(PickupTextClass))
		{
			if (IsValid(PickupTextReference))
			{
				PickupTextReference->PickupActor = Cast<AActor>(this);
				PickupTextReference->ViewPortPosition = Cast<AActor>(this)->GetActorLocation() + FVector(0, 0, 50);
				PickupTextReference->PickupText = TEXT("Press E");
				if (IsValid(CharacterReference))
				{
					CharacterReference->PickupItem.AddDynamic(this, &ASoundItem::PickupSoundItemEvent);
				}
			}
		}
	}
}


void ASoundItem::PickupSoundItemEvent()
{
	if (bIsInRange && !RifaGameInstance->SoundItemHavingMap[(EItem)ThisSoundItemIndex])
	{
		if (!RifaGameInstance->LevelSequencePlayerArr[2])
		{
			if (LevelSequencActor) {
				FMovieSceneSequencePlaybackParams Param;
				FTimerHandle LevelSequenceTimer;
				LevelSequencActor->SequencePlayer->SetPlaybackPosition(Param);
				LevelSequencActor->SequencePlayer->Play();
				GetWorld()->GetTimerManager().SetTimer(LevelSequenceTimer, this, &ASoundItem::OnEndLevelSequence, LevelSequencActor->SequencePlayer->GetDuration().AsSeconds(), false);
				CharacterReference->DisableInput(Cast<APlayerController>(CharacterReference->Controller));
				CharacterReference->SetActorHiddenInGame(true);
			}
		}
		RifaGameInstance->SoundItemHavingMap[(EItem)ThisSoundItemIndex] = true;
		RifaGameInstance->Save();
		PickupTextReference->CloseWidget();
		Destroy();
	}
}

void ASoundItem::OnEndLevelSequence()
{
	CharacterReference->EnableInput(Cast<APlayerController>(CharacterReference->Controller));
	CharacterReference->SetActorHiddenInGame(false);
}