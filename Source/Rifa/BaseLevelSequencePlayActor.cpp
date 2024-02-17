// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseLevelSequencePlayActor.h"
#include "Components/BoxComponent.h"
#include "LevelSequence/Public/LevelSequence.h"
#include "LevelSequence/Public/LevelSequencePlayer.h"
#include "LevelSequence/Public/LevelSequenceActor.h"
#include "Kismet/GameplayStatics.h"
#include "RifaCharacter.h"
#include "MyGameInstance.h"
#include "GameHUD.h"
#include "RifaGameMode.h"
#include "BaseLevelScriptActor.h"

// Sets default values
ABaseLevelSequencePlayActor::ABaseLevelSequencePlayActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	RootComponent = Trigger;
	Trigger->SetCollisionProfileName("Trigger");
}

// Called when the game starts or when spawned
void ABaseLevelSequencePlayActor::BeginPlay()
{
	Super::BeginPlay();

	FMovieSceneSequencePlaybackSettings Settings;
	if (LevelSequenceActor)
	{
		LevelSequence = LevelSequenceActor->LevelSequenceAsset;
		LevelSequencePlayer = LevelSequenceActor->SequencePlayer.Get();
	}

	CharacterReference = Cast<ARifaCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	RifaGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	CurrentLevelScriptActor = Cast<ABaseLevelScriptActor>(GetWorld()->GetLevelScriptActor());
	if (IsValid(RifaGameInstance)) {
		if (RifaGameInstance->LevelSequencePlayerArr[ThisLevelSequenceIndex])
		{
			Destroy();
		}
	}
}
void ABaseLevelSequencePlayActor::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsValid(RifaGameInstance))
	{
		if (RifaGameInstance->LevelSequencePlayerArr[ThisLevelSequenceIndex])
		{
			return;
		}
	}
}

void ABaseLevelSequencePlayActor::EndCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Cast<class ARifaCharacter>(OtherActor) && GetActorEnableCollision())
	{
		bCanPlayLevelSequence = false;
	}
}

void ABaseLevelSequencePlayActor::PlayLevelSequence()
{
}

void ABaseLevelSequencePlayActor::EndLevelSequence()
{
}

// Called every frame
void ABaseLevelSequencePlayActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

