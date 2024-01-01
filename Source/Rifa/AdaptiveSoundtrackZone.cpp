// Fill out your copyright notice in the Description page of Project Settings.


#include "AdaptiveSoundtrackZone.h"
#include "RifaCharacter.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MyGameInstance.h"
#include "BGMAudioComponent.h"
#include "Components/AudioComponent.h"

// Sets default values
AAdaptiveSoundtrackZone::AAdaptiveSoundtrackZone()
{
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));

	SoundTrack = "";
}

// Called when the game starts or when spawned
void AAdaptiveSoundtrackZone::BeginPlay()
{
	Super::BeginPlay();
	RifaGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
}

void AAdaptiveSoundtrackZone::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AAdaptiveSoundtrackZone::OnCharacterOverlap);
}



void AAdaptiveSoundtrackZone::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	RifaGameInstance->SoundTrack = SoundTrack;
	ARifaCharacter* RifaCharacter = Cast<ARifaCharacter>(OtherActor);
	RifaCharacter->Bgm->PlayBgm();
}