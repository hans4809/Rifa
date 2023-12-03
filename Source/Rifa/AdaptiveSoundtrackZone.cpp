// Fill out your copyright notice in the Description page of Project Settings.


#include "AdaptiveSoundtrackZone.h"
#include "RifaCharacter.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MyGameInstance.h"
#include "SoundManagerInstance.h"
#include "Components/AudioComponent.h"

// Sets default values
AAdaptiveSoundtrackZone::AAdaptiveSoundtrackZone()
{
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TRIGGER"));
	BGM1 = CreateDefaultSubobject<UAudioComponent>(TEXT("SOUND"));
	BGM1->SetupAttachment(RootComponent);
	BGM1->bAutoActivate = false;
	SoundToPlay = nullptr;

	SoundTrack = "";
}

// Called when the game starts or when spawned
void AAdaptiveSoundtrackZone::BeginPlay()
{
	Super::BeginPlay();
	RifaGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	SoundManagerInstance = RifaGameInstance->GetSubsystem<USoundManagerInstance>();

	SoundManagerInstance->PlayBGM(SoundToPlay, test);
	BGM1->SetSound(SoundToPlay);
	BGM1->SetBoolParameter("Num1", test[0]);
	BGM1->SetBoolParameter("Num2", test[1]);
	BGM1->SetBoolParameter("Num3", test[2]);
	BGM1->SetBoolParameter("Num4", test[3]);
	BGM1->FadeIn(1.f, 1.f);
	BGM1->Play();
}

void AAdaptiveSoundtrackZone::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AAdaptiveSoundtrackZone::OnCharacterOverlap);
}



void AAdaptiveSoundtrackZone::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	RifaGameInstance->SoundTrack = SoundTrack;
	BGM1->FadeOut(2.f, 0.f);
}