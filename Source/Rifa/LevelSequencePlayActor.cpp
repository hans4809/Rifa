// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelSequencePlayActor.h"
#include "Components/BoxComponent.h"
#include "LevelSequence/Public/LevelSequence.h"
#include "LevelSequence/Public/LevelSequencePlayer.h"
#include "LevelSequence/Public/LevelSequenceActor.h"
#include "Kismet/GameplayStatics.h"
#include "RifaCharacter.h"
#include "Animation/SkeletalMeshActor.h"
#include "MyGameInstance.h"
#include "GameHUD.h"
#include "RifaGameMode.h"
#include "IslandLevelScriptActor.h"



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

	FMovieSceneSequencePlaybackSettings Settings;
	if (LevelSequenceActor)
	{
		LevelSequence = LevelSequenceActor->LevelSequenceAsset;
		LevelSequencePlayer = LevelSequenceActor->SequencePlayer.Get();
	}
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ALevelSequencePlayActor::OnCharacterOverlap);
	Trigger->OnComponentEndOverlap.AddDynamic(this, &ALevelSequencePlayActor::EndCharacterOverlap);
	
	Trigger->SetCollisionProfileName("Trigger");
	CharacterReference = Cast<ARifaCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	RifaGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	GameModeReference = Cast<ARifaGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	CurrentLevelScriptActor = Cast<ABaseLevelScriptActor>(GetWorld()->GetLevelScriptActor());
	if (IsValid(RifaGameInstance)) {
		if (RifaGameInstance->LevelSequencePlayerArr[ThisLevelSequenceIndex])
		{
			Destroy();
		}
	}
}

// Called every frame
void ALevelSequencePlayActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALevelSequencePlayActor::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsValid(RifaGameInstance)) 
	{
		if (RifaGameInstance->LevelSequencePlayerArr[ThisLevelSequenceIndex])
		{
			return;
		}
	}
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
	if (Cast<class ARifaCharacter>(OtherActor) && GetActorEnableCollision())
	{
		bCanPlayLevelSequence = false;
	}
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
	//if (IsValid(CharacterMesh)) 
	//{
	//	Cast<AActor>(CharacterMesh)->SetActorHiddenInGame(true);
	//}
	/*CharacterReference->EnableInput(Cast<APlayerController>(CharacterReference->Controller));
	CharacterReference->SetActorHiddenInGame(false);*/
}
