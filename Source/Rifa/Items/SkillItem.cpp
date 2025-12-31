// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillItem.h"
#include "Data/MyGameInstance.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"
#include "Widget/TutorialWidget.h"
#include "Widget/PickupText.h"
#include <Kismet/GameplayStatics.h>
#include "Character/RifaCharacter.h"
#include "LevelScript/IslandLevelScriptActor.h"
#include "Widget/GameHUD.h"
#include "LevelSequenceActor.h"
#include "LevelSequence.h"
#include "LevelSequencePlayer.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/SphereComponent.h"
#include "Components/AudioComponent.h"
#include "Components/WidgetComponent.h"
#include <Character/RifaPlayerController.h>

ASkillItem::ASkillItem()
{
	Particle = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Particle"));
	Particle->SetupAttachment(RootComponent);
	Particle->SetRelativeRotation(FRotator(90.f, 0, 0));

	Mesh->DestroyComponent();
}

void ASkillItem::BeginPlay()
{
	Super::BeginPlay();
	if (IsValid(RifaGameInstance))
	{
		switch (ThisEnergyType)
		{
		case EEnergyType::Swim:
			Particle->SetAsset(LoadObject<UNiagaraSystem>(nullptr, TEXT("/Script/Niagara.NiagaraSystem'/Game/VFX/VFX_skill_liquid.VFX_skill_liquid'")));
			if (RifaGameInstance->SwimItemArr[ThisSkillItemIndex])
			{
				Destroy();
				return;
			}
			break;
		case EEnergyType::Fly:
			Particle->SetAsset(LoadObject<UNiagaraSystem>(nullptr, TEXT("/Script/Niagara.NiagaraSystem'/Game/VFX/VFX_skill_air.VFX_skill_air'")));
			if (RifaGameInstance->FlyItemArr[ThisSkillItemIndex])
			{
				Destroy();
				return;
			}
			break;
		}
	}

	if (IsValid(CharacterReference))
	{
		CharacterReference->PickupItem.AddDynamic(this, &ASkillItem::PickupEnergyEvent);
	}

	if (IsValid(LevelSequenceActor))
	{
		auto levelSequencePlayer = LevelSequenceActor->SequencePlayer;
		if (levelSequencePlayer->OnFinished.IsBound())
			levelSequencePlayer->OnFinished.Clear();

		levelSequencePlayer->OnFinished.AddDynamic(this, &ASkillItem::EndLevelSequence);

		auto rifaPlayerController = Cast<ARifaPlayerController>(CharacterReference->Controller);
		if (IsValid(rifaPlayerController))
		{
			levelSequencePlayer->OnFinished.AddDynamic(rifaPlayerController, &ARifaPlayerController::OnFinishedLevelSequence);
		}
	}
}

void ASkillItem::PickupEnergyEvent()
{
	if (bIsInRange) 
	{
		switch (ThisEnergyType)
		{
			case EEnergyType::Fly:
				if (RifaGameInstance->FlyItemArr[ThisSkillItemIndex])
				{
					return;
				}
				else
				{
					CharacterReference->SetFlyEnergyNum(CharacterReference->FlyEnergyNum++);
					CharacterReference->MaxFlyEnergyPercent = 0.2f * (CharacterReference->FlyEnergyNum);
					RifaGameInstance->FlyItemArr[ThisSkillItemIndex] = true;
					CharacterReference->FlyEnergyPercent = CharacterReference->MaxFlyEnergyPercent;
					Destroy();
				}
				break;
			case EEnergyType::Swim:
				if (RifaGameInstance->SwimItemArr[ThisSkillItemIndex])
				{
					return;
				}
				else
				{
					CharacterReference->SetSwimEnergyNum(CharacterReference->SwimEnergyNum++);
					CharacterReference->MaxSwimEnergyPercent = 0.2f * (CharacterReference->SwimEnergyNum);
					RifaGameInstance->SwimItemArr[ThisSkillItemIndex] = true;
					CharacterReference->SwimEnergyPercent = CharacterReference->MaxSwimEnergyPercent;

					if (!RifaGameInstance->LevelSequencePlayerArr[1]) 
					{
						if (IsValid(LevelSequenceActor)) 
						{
							auto CurrentLevelScriptActor = Cast<AIslandLevelScriptActor>(GetWorld()->GetLevelScriptActor());
							if (IsValid(CurrentLevelScriptActor))
							{
								FTimerHandle LevelSequenceTimer;
								FMovieSceneSequencePlaybackParams Param;
								auto levelSequencePlayer = LevelSequenceActor->SequencePlayer;
								levelSequencePlayer->SetPlaybackPosition(Param);
								levelSequencePlayer->Play();
							}
						}
					}
					else
					{
						Destroy();
					}
				}
				break;
		}
		AudioComponent->Play();
		SetActorHiddenInGame(true);
		RifaGameInstance->LevelSequencePlayerArr[1] = true;
		WidgetComponent->SetVisibility(false);
		RifaGameInstance->Save();
	}
}

void ASkillItem::EndLevelSequence()
{
	RifaGameInstance->LevelSequencePlayerArr[1] = true;
	Destroy();
}
