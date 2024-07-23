// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseLevelSequencePlayActor.h"
#include "Components/BoxComponent.h"
#include "LevelSequence/Public/LevelSequence.h"
#include "LevelSequence/Public/LevelSequencePlayer.h"
#include "LevelSequence/Public/LevelSequenceActor.h"
#include "Kismet/GameplayStatics.h"
#include "Character/RifaCharacter.h"
#include "Data/MyGameInstance.h"
#include "Widget/GameHUD.h"
#include "LevelScript/BaseLevelScriptActor.h"
#include <Character/RifaPlayerController.h>

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
	CharacterReference = Cast<ARifaCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	auto playerContorller = Cast<ARifaPlayerController>(CharacterReference->Controller);
	RifaGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	CurrentLevelScriptActor = Cast<ABaseLevelScriptActor>(GetWorld()->GetLevelScriptActor());
	if (IsValid(RifaGameInstance)) {
		if (RifaGameInstance->LevelSequencePlayerArr[ThisLevelSequenceIndex])
			Destroy();
	}

	if (IsValid(LevelSequenceActor))
	{
		LevelSequence = LevelSequenceActor->LevelSequenceAsset;
		LevelSequencePlayer = LevelSequenceActor->SequencePlayer.Get();
		/*if (IsValid(playerContorller))
		{
			LevelSequencePlayer->OnPlay.AddDynamic(playerContorller, &ARifaPlayerController::OnStartedLevelSequence);
			LevelSequencePlayer->OnFinished.AddDynamic(playerContorller, &ARifaPlayerController::OnFinishedLevelSequence);
		}*/
	}

}
void ABaseLevelSequencePlayActor::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsValid(RifaGameInstance))
	{
		if (RifaGameInstance->LevelSequencePlayerArr[ThisLevelSequenceIndex])
			return;
	}
}

void ABaseLevelSequencePlayActor::PlayLevelSequence()
{
	if (!RifaGameInstance->LevelSequencePlayerArr[ThisLevelSequenceIndex])
	{
		if (IsValid(CharacterReference) && IsValid(LevelSequencePlayer))
		{
			FTimerHandle LevelSequenceTimer;
			FMovieSceneSequencePlaybackParams Param;
			LevelSequencePlayer->SetPlaybackPosition(Param);
			LevelSequencePlayer->Play();

			if (EndOfLevelSequencePlayerLocation != FVector(0, 0, 0))
				CharacterReference->SetActorLocationAndRotation(EndOfLevelSequencePlayerLocation, EndOfLevelSequencePlayerRotation);

			RifaGameInstance->LevelSequencePlayerArr[ThisLevelSequenceIndex] = true;
		}
	}
}

void ABaseLevelSequencePlayActor::EndLevelSequence()
{
	Destroy();
}

