// Fill out your copyright notice in the Description page of Project Settings.


#include "Gimmick/FogActor.h"
#include "Components/BoxComponent.h"
#include <Character/RifaCharacter.h>
#include <Kismet/GameplayStatics.h>
#include "Data/MyGameInstance.h"

// Sets default values
AFogActor::AFogActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MESH"));
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));

	RootComponent = Mesh;
	Trigger->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AFogActor::BeginPlay()
{
	Super::BeginPlay();
	switch (ThisForestType)
	{
	case EForestType::Island:
		if(auto GameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld())))
		{
			if(GameInstance->bClearIslandForest)
			{
				Mesh->DestroyComponent();
			}
		}
		break;
	case EForestType::Field:
		if(auto GameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld())))
		{
			if(GameInstance->bClearFieldForest)
			{
				Mesh->DestroyComponent();
			}
		}
		break;
	}
	
}

// Called every frame
void AFogActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFogActor::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<ARifaCharacter>(OtherActor)) 
	{
		if(auto GameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld())))
		{
			switch (ThisForestType)
			{
			case EForestType::Island:
				if(GameInstance->SwimItemArr[3] && GameInstance->SoundItemHavingMap[(EItem)3])
				{
					GameInstance->bClearIslandForest = true;
					Mesh->DestroyComponent();
				}
				break;
			case EForestType::Field:
				if(GameInstance->FlyItemArr[4] && GameInstance->SoundItemHavingMap[(EItem)13] && GameInstance->SoundItemHavingMap[(EItem)14])
				{
					GameInstance->bClearFieldForest = true;
					Mesh->DestroyComponent();
				}
				break;
			default:
				break;
			}
		}
	}
}

