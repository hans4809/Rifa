// Fill out your copyright notice in the Description page of Project Settings.


#include "SoundItem.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"
#include "Data/MyGameInstance.h"
#include "Widget/PickupText.h"
#include <Kismet/GameplayStatics.h>
#include "Character/RifaCharacter.h"
#include "LevelSequenceActor.h"
#include "LevelSequence.h"
#include "LevelSequencePlayer.h"
#include <LevelScript/IslandLevelScriptActor.h>
#include "Widget/GameHUD.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/SphereComponent.h"
#include "Sound/BGMAudioComponent.h"
#include "Widget/CollectionWidget.h"
#include "Sound/AmbientSound.h"
#include "Components/AudioComponent.h"
#include "Components/WidgetComponent.h"
#include <Character/RifaPlayerController.h>

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
		if (IsValid(CollectionWidgetClass)) 
			CollectionWidgetReference = CreateWidget<UCollectionWidget>(GetWorld(), CollectionWidgetClass);

		if (IsValid(CharacterReference))
			CharacterReference->PickupItem.AddDynamic(this, &ASoundItem::PickupSoundItemEvent);

		if (IsValid(LevelSequencActor))
		{
			auto levelSequencePlayer = LevelSequencActor->SequencePlayer;
			if (levelSequencePlayer->OnFinished.IsBound())
				levelSequencePlayer->OnFinished.Clear();

			levelSequencePlayer->OnFinished.AddDynamic(this, &ASoundItem::OnEndLevelSequence);

			auto rifaPlayerController = Cast<ARifaPlayerController>(CharacterReference->Controller);
			if (IsValid(rifaPlayerController))
			{
				levelSequencePlayer->OnFinished.AddDynamic(rifaPlayerController, &ARifaPlayerController::OnFinishedLevelSequence);
			}
		}
	}
}


void ASoundItem::PickupSoundItemEvent()
{
	if (bIsInRange && !RifaGameInstance->SoundItemHavingMap[(EItem)ThisSoundItemIndex])
	{
		AudioComponent->Play();
		auto CurrentLevelScriptActor = Cast<AIslandLevelScriptActor>(GetWorld()->GetLevelScriptActor());
		if (!RifaGameInstance->LevelSequencePlayerArr[2])
		{
			if (LevelSequencActor) 
			{
				if (IsValid(CurrentLevelScriptActor))
				{
					FTimerHandle LevelSequenceTimer;
					FMovieSceneSequencePlaybackParams Param;
					auto levelSequencePlayer = LevelSequencActor->SequencePlayer;
					levelSequencePlayer->SetPlaybackPosition(Param);
					levelSequencePlayer->Play();
					CurrentLevelScriptActor->BGMActor->GetAudioComponent()->SetPaused(true);
				}
			}
		}

		RifaGameInstance->SoundItemHavingMap[(EItem)ThisSoundItemIndex] = true;
		RifaGameInstance->SoundItemOnOffMap[(EItem)ThisSoundItemIndex] = true;
		if (IsValid(RifaGameInstance) && IsValid(CurrentLevelScriptActor))
		{
			for (int i = 0; i < RifaGameInstance->SoundItemOnOffMap.Num(); i++)
			{
				FName Parameter = FName(FString::Printf(TEXT("Inst%d"), i));
				if (RifaGameInstance->SoundItemHavingMap[EItem(i)])
				{
					if (RifaGameInstance->SoundItemOnOffMap[EItem(i)])
						CurrentLevelScriptActor->BGMActor->GetAudioComponent()->SetFloatParameter(Parameter, 1.f);
					else
						CurrentLevelScriptActor->BGMActor->GetAudioComponent()->SetFloatParameter(Parameter, 0.f);
				}
				else
					CurrentLevelScriptActor->BGMActor->GetAudioComponent()->SetFloatParameter(Parameter, 0.f);
			}
		}
		RifaGameInstance->LevelSequencePlayerArr[2] = true;
		RifaGameInstance->Save();
		WidgetComponent->SetVisibility(false);
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
			CurrentLevelScriptActor->BGMActor->GetAudioComponent()->SetPaused(false);

		if (IsValid(CollectionWidgetReference))
		{
			CollectionWidgetReference->Init();

			auto pc = Cast<ARifaPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
			if(IsValid(pc))
			{
				if (IsValid(pc->GameHUDWidgetAsset))
				{
					CollectionWidgetReference->ParentWidget = pc->GameHUDWidgetAsset;
				}
			}
		}

		Destroy();
	}
}