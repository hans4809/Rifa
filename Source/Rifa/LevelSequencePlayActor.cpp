// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelSequencePlayActor.h"
#include "Components/BoxComponent.h"
#include "LevelSequence/Public/LevelSequence.h"
#include "LevelSequence/Public/LevelSequencePlayer.h"
#include "LevelSequence/Public/LevelSequenceActor.h"
#include "Kismet/GameplayStatics.h"
#include "RifaCharacter.h"
#include "Animation/SkeletalMeshActor.h"
#include "LevelSequenceCharacterActor.h"



// Sets default values
ALevelSequencePlayActor::ALevelSequencePlayActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	RootComponent = Trigger;
}

// Called when the game starts or when spawned
void ALevelSequencePlayActor::BeginPlay()
{
	Super::BeginPlay();
	if (IsValid(CharacterMesh)) 
	{
		Cast<AActor>(CharacterMesh)->SetActorHiddenInGame(true);
	}

	FMovieSceneSequencePlaybackSettings Settings;
	if (LevelSequenceActor)
	{
		LevelSequence = LevelSequenceActor->LevelSequenceAsset;
		LevelSequencePlayer = LevelSequenceActor->SequencePlayer.Get();
	}
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ALevelSequencePlayActor::OnCharacterOverlap);
	Trigger->SetCollisionProfileName("Trigger");
	CharacterReference = Cast<ARifaCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

// Called every frame
void ALevelSequencePlayActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALevelSequencePlayActor::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<class ARifaCharacter>(OtherActor) && GetActorEnableCollision())
	{
		if (IsValid(CharacterMesh)) 
		{
			Cast<AActor>(CharacterMesh)->SetActorHiddenInGame(false);
		}
		FMovieSceneSequencePlaybackParams Param;
		LevelSequencePlayer->SetPlaybackPosition(Param);
		LevelSequencePlayer->Play();
		GetWorld()->GetTimerManager().SetTimer(LevelSequenceTimer, this, &ALevelSequencePlayActor::EndLevelSequence, LevelSequencePlayer->GetDuration().AsSeconds(), false);
		CharacterReference->DisableInput(Cast<APlayerController>(CharacterReference->Controller));
		CharacterReference->SetActorHiddenInGame(true);
		CharacterReference->SetActorLocation(EndOfLevelSequencePlayerLocation);
	}
}

void ALevelSequencePlayActor::EndLevelSequence()
{
	if (IsValid(CharacterMesh)) 
	{
		Cast<AActor>(CharacterMesh)->SetActorHiddenInGame(true);
	}
	CharacterReference->EnableInput(Cast<APlayerController>(CharacterReference->Controller));
	CharacterReference->SetActorHiddenInGame(false);
}
