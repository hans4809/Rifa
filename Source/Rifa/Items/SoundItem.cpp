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
#include <LevelScript/IslandLevelScriptActor.h>
#include "Widget/GameHUD.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/SphereComponent.h"
#include "Sound/BGMAudioComponent.h"
#include "Widget/CollectionWidget.h"

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
		if (IsValid(CollectionWidgetClass)) 
		{
			CollectionWidgetReference = CreateWidget<UCollectionWidget>(GetWorld(), CollectionWidgetClass);
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
				auto CurrentLevelScriptActor = Cast<AIslandLevelScriptActor>(GetWorld()->GetLevelScriptActor());
				if (IsValid(CurrentLevelScriptActor))
				{
					FTimerHandle LevelSequenceTimer;
					FMovieSceneSequencePlaybackParams Param;
					CharacterReference->DisableInput(Cast<APlayerController>(CharacterReference->Controller));
					//CurrentLevelScriptActor->GameHUDWidgetAsset->CloseWidget();
					UWidgetLayoutLibrary::RemoveAllWidgets(GetWorld());
					auto LevelSequncePlayer = LevelSequencActor->SequencePlayer.Get();
					LevelSequncePlayer->SetPlaybackPosition(Param);
					LevelSequncePlayer->Play();
					GetWorld()->GetTimerManager().SetTimer(LevelSequenceTimer, this, &ASoundItem::OnEndLevelSequence, LevelSequncePlayer->GetDuration().AsSeconds(), false);
				}
			}
		}
		RifaGameInstance->SoundItemHavingMap[(EItem)ThisSoundItemIndex] = true;
		RifaGameInstance->SoundItemOnOffMap[(EItem)ThisSoundItemIndex] = true;
		RifaGameInstance->LevelSequencePlayerArr[2] = true;
		//CharacterReference->Bgm->CrossfadeSound();
		RifaGameInstance->Save();
		PickupTextReference->CloseWidget();
		SetActorHiddenInGame(true);
		Trigger->DestroyComponent();
	}
}

void ASoundItem::OnEndLevelSequence()
{
	if (IsValid(CharacterReference)) 
	{
		RifaGameInstance->LevelSequencePlayerArr[2] = true;
		auto CurrentLevelScriptActor = Cast<AIslandLevelScriptActor>(GetWorld()->GetLevelScriptActor());
		if (IsValid(CurrentLevelScriptActor))
		{
			if (IsValid(CurrentLevelScriptActor->GameHUDWidgetAsset))
			{
				CurrentLevelScriptActor->GameHUDWidgetAsset->Init();
			}
		}
		CharacterReference->EnableInput(Cast<APlayerController>(CharacterReference->Controller));
		if (IsValid(CollectionWidgetReference)) 
		{
			CollectionWidgetReference->Init();
		}
	}
}