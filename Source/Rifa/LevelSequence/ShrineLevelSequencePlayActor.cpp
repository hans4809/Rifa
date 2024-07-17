// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelSequence/ShrineLevelSequencePlayActor.h"
#include "Data/MyGameInstance.h"
#include "NiagaraComponent.h"
#include "Components/BoxComponent.h"
#include "LevelSequence/Public/LevelSequence.h"
#include "LevelSequence/Public/LevelSequencePlayer.h"
#include "LevelSequence/Public/LevelSequenceActor.h"
#include "Character/RifaCharacter.h"
#include "LevelScript/BaseLevelScriptActor.h"
#include "Widget/GameHUD.h"

AShrineLevelSequencePlayActor::AShrineLevelSequencePlayActor()
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

void AShrineLevelSequencePlayActor::BeginPlay()
{
	Super::BeginPlay();
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AShrineLevelSequencePlayActor::OnCharacterOverlap);
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

void AShrineLevelSequencePlayActor::PlayLevelSequence()
{
	Super::PlayLevelSequence();
	
	FTimerHandle LevelSequenceTimer;
	GetWorld()->GetTimerManager().SetTimer(LevelSequenceTimer, this, &AShrineLevelSequencePlayActor::EndLevelSequence, LevelSequencePlayer->GetDuration().AsSeconds(), false);
}

void AShrineLevelSequencePlayActor::EndLevelSequence()
{
	Super::EndLevelSequence();
	switch (ThisEnergyType)
	{
	case EEnergyType::Fly:
		if (RifaGameInstance->bCanFly)
			return;
		else
			RifaGameInstance->bCanFly = true;
		break;
	case EEnergyType::Swim:
		if (RifaGameInstance->bCanSwim)
			return;
		else
			RifaGameInstance->bCanSwim = true;
	}
	Particle->SetActive(false);
}

void AShrineLevelSequencePlayActor::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnCharacterOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	if (Cast<class ARifaCharacter>(OtherActor))
	{
		PlayLevelSequence();
	}
}
