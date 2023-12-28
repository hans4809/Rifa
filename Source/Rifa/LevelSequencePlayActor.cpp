// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelSequencePlayActor.h"
#include "Components/BoxComponent.h"
#include "LevelSequence/Public/LevelSequence.h"
#include "LevelSequence/Public/LevelSequencePlayer.h"
#include "LevelSequence/Public/LevelSequenceActor.h"
#include "Kismet/GameplayStatics.h"
#include "RifaCharacter.h"
#include "Animation/SkeletalMeshActor.h"



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
	Cast<AActor>(CharacterMesh)->SetActorHiddenInGame(true);
	FMovieSceneSequencePlaybackSettings Settings;
	Settings.bAutoPlay = false;
	Settings.bPauseAtEnd = true;
	if (LevelSequnce && LevelSequenceActor) 
	{
		LevelSequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), LevelSequnce, Settings, LevelSequenceActor);
	}
}

void ALevelSequencePlayActor::EndLevelSequence()
{
	Cast<AActor>(CharacterMesh)->SetActorHiddenInGame(true);
	auto CharacterReference = Cast<ARifaCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	CharacterReference->EnableInput(Cast<APlayerController>(CharacterReference->Controller));
	CharacterReference->SetActorHiddenInGame(false);
}

// Called every frame
void ALevelSequencePlayActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALevelSequencePlayActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (LevelSequencePlayer&& Cast<class ARifaCharacter>(OtherActor)) 
	{
		Cast<AActor>(CharacterMesh)->SetActorHiddenInGame(false);
		LevelSequencePlayer->Play();
		GetWorld()->GetTimerManager().SetTimer(LevelSequenceTimer, this, &ALevelSequencePlayActor::EndLevelSequence, LevelSequencePlayer->GetEndTime().AsSeconds(), false);
		auto CharacterReference = Cast<ARifaCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		CharacterReference->DisableInput(Cast<APlayerController>(CharacterReference->Controller));
		SetActorEnableCollision(false);
		CharacterReference->SetActorHiddenInGame(true);
	}
}

