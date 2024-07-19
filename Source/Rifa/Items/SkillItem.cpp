// Fill out your copyright notice in the Description page of Project Settings.


#include "SkillItem.h"
#include "Data/MyGameInstance.h"
#include "NiagaraComponent.h"
#include "Widget/TutorialWidget.h"
#include "Widget/PickupText.h"
#include <Kismet/GameplayStatics.h>
#include "Character/RifaCharacter.h"
#include "LevelScript/IslandLevelScriptActor.h"
#include "Widget/GameHUD.h"
#include "LevelSequence/Public/LevelSequence.h"
#include "LevelSequence/Public/LevelSequencePlayer.h"
#include "LevelSequence/Public/LevelSequenceActor.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/SphereComponent.h"
#include "Components/AudioComponent.h"
#include "Components/WidgetComponent.h"

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
			}
			break;
		case EEnergyType::Fly:
			Particle->SetAsset(LoadObject<UNiagaraSystem>(nullptr, TEXT("/Script/Niagara.NiagaraSystem'/Game/VFX/VFX_skill_air.VFX_skill_air'")));
			if (RifaGameInstance->FlyItemArr[ThisSkillItemIndex])
			{
				Destroy();
			}
			break;
		}
	}
	//if (IsValid(PickupTextReference)) 
	//{
	//	PickupTextReference->PickupActor = Cast<AActor>(this);
	//	PickupTextReference->ViewPortPosition = Cast<AActor>(this)->GetActorLocation() + FVector(0, 0, 50);
	//	PickupTextReference->PickupText = TEXT("Press E");
	//}
	if (IsValid(CharacterReference))
	{
		CharacterReference->PickupItem.AddDynamic(this, &ASkillItem::PickupEnergyEvent);
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
						Destroy();
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
					if (CharacterReference->SwimEnergyNum < 5)
					{
						CharacterReference->SwimEnergyNum++;
						CharacterReference->MaxSwimEnergyPercent += 0.2f;
						RifaGameInstance->SwimItemArr[ThisSkillItemIndex] = true;
						CharacterReference->SwimEnergyPercent = CharacterReference->MaxSwimEnergyPercent;
					}
					if (!RifaGameInstance->LevelSequencePlayerArr[1]) 
					{
						if (IsValid(LevelSequenceActor)) 
						{
							auto CurrentLevelScriptActor = Cast<AIslandLevelScriptActor>(GetWorld()->GetLevelScriptActor());
							if (IsValid(CurrentLevelScriptActor))
							{
								FTimerHandle LevelSequenceTimer;
								FMovieSceneSequencePlaybackParams Param;
								CharacterReference->DisableInput(Cast<APlayerController>(CharacterReference->Controller));
								//CurrentLevelScriptActor->GameHUDWidgetAsset->CloseWidget();
								auto LevelSequncePlayer = LevelSequenceActor->SequencePlayer.Get();
								LevelSequncePlayer->SetPlaybackPosition(Param);
								LevelSequncePlayer->Play();
								GetWorld()->GetTimerManager().SetTimer(LevelSequenceTimer, this, &ASkillItem::EndLevelSequence, LevelSequncePlayer->GetDuration().AsSeconds(), false);
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
	if (IsValid(CharacterReference)) 
	{
		RifaGameInstance->LevelSequencePlayerArr[1] = true;
		auto CurrentLevelScriptActor = Cast<AIslandLevelScriptActor>(GetWorld()->GetLevelScriptActor());
		if (IsValid(CurrentLevelScriptActor))
		{
			/*if (IsValid(CurrentLevelScriptActor->GameHUDWidgetAsset))
			{
				CurrentLevelScriptActor->GameHUDWidgetAsset->Init();
			}*/
		}
		CharacterReference->EnableInput(Cast<APlayerController>(CharacterReference->Controller));
		Destroy();
	}
}
