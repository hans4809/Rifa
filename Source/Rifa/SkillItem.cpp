// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillItem.h"
#include "MyGameInstance.h"
#include "NiagaraComponent.h"
#include "TutorialWidget.h"
#include "PickupText.h"
#include <Kismet/GameplayStatics.h>
#include "RifaCharacter.h"
#include "IslandLevelScriptActor.h"
#include "GameHUD.h"
#include "LevelSequence/Public/LevelSequence.h"
#include "LevelSequence/Public/LevelSequencePlayer.h"
#include "LevelSequence/Public/LevelSequenceActor.h"

ASkillItem::ASkillItem()
{
	Particle = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Particle"));
	Particle->SetupAttachment(RootComponent);
	Particle->SetRelativeRotation(FRotator(90.f, 0, 0));
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
				Particle->SetActive(false);
			}
			break;
		case EEnergyType::Fly:
			Particle->SetAsset(LoadObject<UNiagaraSystem>(nullptr, TEXT("/Script/Niagara.NiagaraSystem'/Game/VFX/VFX_skill_air.VFX_skill_air'")));
			if (RifaGameInstance->FlyItemArr[ThisSkillItemIndex])
			{
				Particle->SetActive(false);
			}
			break;
		}
	}
	if (IsValid(PickupTextReference)) 
	{
		PickupTextReference->PickupActor = Cast<AActor>(this);
		PickupTextReference->ViewPortPosition = Cast<AActor>(this)->GetActorLocation() + FVector(0, 0, 50);
		PickupTextReference->PickupText = TEXT("Press E");
		if (IsValid(CharacterReference)) 
		{
			CharacterReference->PickupItem.AddDynamic(this, &ASkillItem::PickupEnergyEvent);
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
					if (CharacterReference->FlyEnergyNum < 5)
					{
						CharacterReference->FlyEnergyNum++;
						CharacterReference->MaxFlyEnergyPercent += 0.2f;
						RifaGameInstance->FlyItemArr[ThisSkillItemIndex] = true;
						CharacterReference->FlyEnergyPercent = CharacterReference->MaxFlyEnergyPercent;
					}
				}
				break;
			case EEnergyType::Swim:
				if (RifaGameInstance->SwimItemArr[ThisSkillItemIndex])
				{
					return;
				}
				else
				{
					if (RifaGameInstance->LevelSequencePlayerArr[8]) 
					{
						if (!(LevelSequenceActor.IsNull())) 
						{
							auto CurrentLevelScriptActor = Cast<AIslandLevelScriptActor>(GetWorld()->GetLevelScriptActor());
							if (IsValid(CurrentLevelScriptActor))
							{
								FTimerHandle LevelSequenceTimer;
								FMovieSceneSequencePlaybackParams Param;
								CharacterReference->DisableInput(Cast<APlayerController>(CharacterReference->Controller));
								CurrentLevelScriptActor->GameHUDWidgetAsset->CloseWidget();
								auto LevelSequncePlayer = LevelSequenceActor->SequencePlayer.Get();
								LevelSequncePlayer->SetPlaybackPosition(Param);
								LevelSequncePlayer->Play();
								GetWorld()->GetTimerManager().SetTimer(LevelSequenceTimer, this, &ASkillItem::EndLevelSequence, LevelSequncePlayer->GetDuration().AsSeconds(), false);
							}

						}
					}
					if (CharacterReference->SwimEnergyNum < 5)
					{
						CharacterReference->SwimEnergyNum++;
						CharacterReference->MaxSwimEnergyPercent += 0.2f;
						RifaGameInstance->SwimItemArr[ThisSkillItemIndex] = true;
						CharacterReference->SwimEnergyPercent = CharacterReference->MaxSwimEnergyPercent;
					}
				}
				break;
		}
		Particle->SetActive(false);
	}
}

void ASkillItem::EndLevelSequence()
{
	if (IsValid(CharacterReference)) {
		auto CurrentLevelScriptActor = Cast<AIslandLevelScriptActor>(GetWorld()->GetLevelScriptActor());
		if (IsValid(CurrentLevelScriptActor->GameHUDWidgetAsset))
		{
			CurrentLevelScriptActor->GameHUDWidgetAsset->Init();
		}
		CharacterReference->EnableInput(Cast<APlayerController>(CharacterReference->Controller));
		Destroy();
	}
}
