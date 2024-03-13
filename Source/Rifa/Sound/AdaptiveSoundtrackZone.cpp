// Fill out your copyright notice in the Description page of Project Settings.


#include "AdaptiveSoundtrackZone.h"
#include "Character/RifaCharacter.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Data/MyGameInstance.h"
#include "BGMAudioComponent.h"
#include "Components/AudioComponent.h"
#include "LevelScript/BaseLevelScriptActor.h"
#include "Sound/AmbientSound.h"

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
	CurrentLevelScriptActor = Cast<ABaseLevelScriptActor>(GetWorld()->GetLevelScriptActor());
}

void AAdaptiveSoundtrackZone::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AAdaptiveSoundtrackZone::OnCharacterOverlap);
}



void AAdaptiveSoundtrackZone::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<ARifaCharacter>(OtherActor)) {
		if (RifaGameInstance->SoundTrack != SoundTrack)
		{
			RifaGameInstance->SoundTrack = SoundTrack;
		}
		if (RifaGameInstance->BGMIndex != BGMIndex) 
		{
			RifaGameInstance->BGMIndex = BGMIndex;
		}
		if (IsValid(CurrentLevelScriptActor))
		{
			if (CurrentLevelScriptActor->BGMActor)
			{
				CurrentLevelScriptActor->BGMActor->GetAudioComponent()->SetFloatParameter(TEXT("BGM"), (float)BGMIndex);
			}
		}
	}
	
	
}