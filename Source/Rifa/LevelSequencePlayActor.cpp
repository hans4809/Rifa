// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelSequencePlayActor.h"
#include "Components/BoxComponent.h"
#include "LevelSequence/Public/LevelSequence.h"
#include "LevelSequence/Public/LevelSequencePlayer.h"
#include "LevelSequence/Public/LevelSequenceActor.h"



// Sets default values
ALevelSequencePlayActor::ALevelSequencePlayActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	Trigger->SetCollisionProfileName("Trigger");
	RootComponent = Trigger;
}

// Called when the game starts or when spawned
void ALevelSequencePlayActor::BeginPlay()
{
	Super::BeginPlay();
	CharacterMesh->SetActorHiddenInGame(true);
	FMovieSceneSequencePlaybackSettings Settings;
	Settings.bAutoPlay = false;
	Settings.bPauseAtEnd = true;
	if (LevelSequnce && LevelSequenceActor) 
	{
		LevelSequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), LevelSequnce, Settings, LevelSequenceActor);
	}
}

// Called every frame
void ALevelSequencePlayActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALevelSequencePlayActor::NotifyActorBeginOverlap(AActor* otherActor)
{
	Super::NotifyActorBeginOverlap(otherActor);

	if (LevelSequencePlayer) 
	{
		CharacterMesh->SetActorHiddenInGame(false);
		LevelSequencePlayer->Play();
	}
}

