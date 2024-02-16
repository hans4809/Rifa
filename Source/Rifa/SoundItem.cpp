// Fill out your copyright notice in the Description page of Project Settings.


#include "SoundItem.h"
#include "NiagaraComponent.h"
#include "MyGameInstance.h"
#include "PickupText.h"
#include <Kismet/GameplayStatics.h>
#include "RifaCharacter.h"

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
	if (RifaGameInstance->SoundItemHavingMap[(Item)ThisSoundItemIndex])
	{
		Destroy();
		return;
	}
	else
	{
		ItemInfo.ItemActor = Cast<AActor>(this);
		ItemInfo.ItemImage = CustomImage;
		ItemInfo.ItemName = CustomItemName;
		//Mesh->SetStaticMesh(CustomStaticMesh);
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
	if (bIsInRange && !RifaGameInstance->SoundItemHavingMap[(Item)ThisSoundItemIndex])
	{
		RifaGameInstance->SoundItemHavingMap[(Item)ThisSoundItemIndex] = true;
		RifaGameInstance->Save();
		PickupTextReference->CloseWidget();
		Destroy();
	}
}


