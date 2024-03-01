// Fill out your copyright notice in the Description page of Project Settings.


#include "ShrinItem.h"
#include "Data/MyGameInstance.h"
#include "Character/RifaCharacter.h"
#include "NiagaraComponent.h"
#include "Widget/PickupText.h"
#include <Kismet/GameplayStatics.h>


AShrinItem::AShrinItem()
{
	Particle = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Particle"));
	Particle->SetupAttachment(RootComponent);
	Particle->SetRelativeRotation(FRotator(90.f, 0, 0));
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> PARTICLE(TEXT("/Script/Niagara.NiagaraSystem'/Game/VFX/VFX_shrine.VFX_shrine'"));
	if (PARTICLE.Succeeded()) 
	{
		Particle->SetAsset(PARTICLE.Object);
	}
}

void AShrinItem::BeginPlay()
{
	Super::BeginPlay();
	switch (ThisEnergyType)
	{
	case EEnergyType::Swim:
		if(RifaGameInstance->bCanSwim)
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
	if (IsValid(PickupTextReference))
	{
		PickupTextReference->PickupActor = Cast<AActor>(this);
		PickupTextReference->ViewPortPosition = Cast<AActor>(this)->GetActorLocation() + FVector(0, 0, 50);
		PickupTextReference->PickupText = TEXT("Press E");
		if (IsValid(CharacterReference))
		{
			CharacterReference->PickupItem.AddDynamic(this, &AShrinItem::PickupShrineItem);
		}
	}
}

void AShrinItem::PickupShrineItem()
{
	if (bIsInRange)
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
	}
}
