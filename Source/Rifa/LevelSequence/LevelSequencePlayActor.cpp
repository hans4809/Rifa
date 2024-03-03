// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelSequencePlayActor.h"
#include "Components/BoxComponent.h"
#include "LevelSequence/Public/LevelSequence.h"
#include "LevelSequence/Public/LevelSequencePlayer.h"
#include "LevelSequence/Public/LevelSequenceActor.h"
#include "Kismet/GameplayStatics.h"
#include "Character/RifaCharacter.h"
#include "Animation/SkeletalMeshActor.h"
#include "Data/MyGameInstance.h"
#include "Widget/GameHUD.h"
#include "LevelScript/IslandLevelScriptActor.h"



// Sets default values
ALevelSequencePlayActor::ALevelSequencePlayActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ALevelSequencePlayActor::BeginPlay()
{
	Super::BeginPlay();
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ALevelSequencePlayActor::OnCharacterOverlap);
	Trigger->OnComponentEndOverlap.AddDynamic(this, &ALevelSequencePlayActor::EndCharacterOverlap);
}

// Called every frame
void ALevelSequencePlayActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



void ALevelSequencePlayActor::PlayLevelSequence()
{
	if (bCanPlayLevelSequence && !RifaGameInstance->LevelSequencePlayerArr[ThisLevelSequenceIndex])
	{
		if (IsValid(CharacterReference) && IsValid(LevelSequencePlayer))
		{
			if (IsValid(CurrentLevelScriptActor->GameHUDWidgetAsset))
			{
				CurrentLevelScriptActor->GameHUDWidgetAsset->CloseWidget();
			}
			CharacterReference->DisableInput(Cast<APlayerController>(CharacterReference->Controller));
			FTimerHandle LevelSequenceTimer;
			FMovieSceneSequencePlaybackParams Param;
			LevelSequencePlayer->SetPlaybackPosition(Param);
			LevelSequencePlayer->Play();
			GetWorld()->GetTimerManager().SetTimer(LevelSequenceTimer, this, &ALevelSequencePlayActor::EndLevelSequence, LevelSequencePlayer->GetDuration().AsSeconds(), false);

			RifaGameInstance->LevelSequencePlayerArr[ThisLevelSequenceIndex] = true;
		}
	}
}

void ALevelSequencePlayActor::EndLevelSequence()
{
	if (IsValid(CharacterReference)) {
		if (IsValid(CurrentLevelScriptActor->GameHUDWidgetAsset))
		{
			CurrentLevelScriptActor->GameHUDWidgetAsset->Init();
		}
		CharacterReference->EnableInput(Cast<APlayerController>(CharacterReference->Controller));
		Destroy();
	}
}

void ALevelSequencePlayActor::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnCharacterOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	if (ThisLevelSequenceType == ELevelSequenceType::Trigger)
	{
		if (Cast<class ARifaCharacter>(OtherActor) && GetActorEnableCollision())
		{
			bCanPlayLevelSequence = true;
			PlayLevelSequence();
		}
	}
	else
	{
		if (Cast<class ARifaCharacter>(OtherActor) && GetActorEnableCollision())
		{
			bCanPlayLevelSequence = true;
		}
	}
}

void ALevelSequencePlayActor::EndCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::EndCharacterOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex);
	if (Cast<class ARifaCharacter>(OtherActor) && GetActorEnableCollision())
	{
		bCanPlayLevelSequence = false;
	}
}