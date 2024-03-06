// Fill out your copyright notice in the Description page of Project Settings.


#include "FinalLevelSequencePlayActor.h"
#include "Data/MyGameInstance.h"
#include "NiagaraComponent.h"
#include "Components/BoxComponent.h"
#include "LevelSequence/Public/LevelSequence.h"
#include "LevelSequence/Public/LevelSequencePlayer.h"
#include "LevelSequence/Public/LevelSequenceActor.h"
#include "Character/RifaCharacter.h"
#include "LevelScript/BaseLevelScriptActor.h"
#include "Widget/GameHUD.h"


AFinalLevelSequencePlayActor::AFinalLevelSequencePlayActor()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	Particle = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Particle"));
	Particle->SetupAttachment(RootComponent);
	Particle->SetRelativeRotation(FRotator(90.f, 0, 0));
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> PARTICLE(TEXT("/Script/Niagara.NiagaraSystem'/Game/VFX/VFX_shrine.VFX_shrine'"));
	if (PARTICLE.Succeeded())
	{
		Particle->SetAsset(PARTICLE.Object);
	}
}

void AFinalLevelSequencePlayActor::BeginPlay()
{
	Super::BeginPlay();
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AFinalLevelSequencePlayActor::OnCharacterOverlap);
	switch (ThisEnergyType)
	{
	case EEnergyType::Swim:
		if (RifaGameInstance->bCanSwim)
		{
			Particle->SetActive(false);
		}
		break;
	case EEnergyType::Fly:
		if (RifaGameInstance->bCanFly)
		{
			Particle->SetActive(false);
		}
		break;
	}
}

void AFinalLevelSequencePlayActor::PlayLevelSequence()
{
	if (IsValid(CharacterReference) && IsValid(LevelSequencePlayer))
	{
		if (IsValid(CurrentLevelScriptActor))
		{
			if (IsValid(CurrentLevelScriptActor->GameHUDWidgetAsset))
			{
				CurrentLevelScriptActor->GameHUDWidgetAsset->CloseWidget();
			}
		}
		CharacterReference->DisableInput(Cast<APlayerController>(CharacterReference->Controller));
		FTimerHandle LevelSequenceTimer;
		FMovieSceneSequencePlaybackParams Param;
		LevelSequencePlayer->SetPlaybackPosition(Param);
		LevelSequencePlayer->Play();
		GetWorld()->GetTimerManager().SetTimer(LevelSequenceTimer, this, &AFinalLevelSequencePlayActor::EndLevelSequence, LevelSequencePlayer->GetDuration().AsSeconds(), false);

		RifaGameInstance->LevelSequencePlayerArr[ThisLevelSequenceIndex] = true;
	}
}

void AFinalLevelSequencePlayActor::EndLevelSequence()
{
	switch (ThisEnergyType)
	{
	case EEnergyType::Fly:
		if (RifaGameInstance->bCanFly)
		{
			return;
		}
		else
		{
			RifaGameInstance->bCanFly = true;
		}
		break;
	case EEnergyType::Swim:
		if (RifaGameInstance->bCanSwim)
		{
			return;
		}
		else
		{
			RifaGameInstance->bCanSwim = true;
		}
	}
	Particle->SetActive(false);
	Super::EndLevelSequence();

}

void AFinalLevelSequencePlayActor::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnCharacterOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	if (Cast<class ARifaCharacter>(OtherActor))
	{
		PlayLevelSequence();
	}
}
