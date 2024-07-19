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
		//if (IsValid(PickupTextClass))
		//{
		//	if (IsValid(PickupTextReference))
		//	{
		//		PickupTextReference->PickupActor = Cast<AActor>(this);
		//		PickupTextReference->ViewPortPosition = Cast<AActor>(this)->GetActorLocation() + FVector(0, 0, 50);
		//		PickupTextReference->PickupText = TEXT("Press E");
		//		
		//	}
		//}
		if (IsValid(CollectionWidgetClass)) 
			CollectionWidgetReference = CreateWidget<UCollectionWidget>(GetWorld(), CollectionWidgetClass);
		if (IsValid(CharacterReference))
			CharacterReference->PickupItem.AddDynamic(this, &ASoundItem::PickupSoundItemEvent);

		if (IsValid(LevelSequencActor))
		{
			auto levelSequencePlayer = LevelSequencActor->SequencePlayer;
			levelSequencePlayer->OnFinished.AddDynamic(this, &ASoundItem::OnEndLevelSequence);

			auto rifaPlayerController = Cast<ARifaPlayerController>(CharacterReference->Controller);
			if (IsValid(rifaPlayerController))
			{
				levelSequencePlayer->OnPlay.AddDynamic(rifaPlayerController, &ARifaPlayerController::OnStartedLevelSequence);
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
			if (LevelSequencActor) {
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
		else 
		{
			Destroy();
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
			CollectionWidgetReference->Init();

		Destroy();
	}
}