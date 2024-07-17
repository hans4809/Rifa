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
	RifaGameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	CurrentLevelScriptActor = Cast<ABaseLevelScriptActor>(GetWorld()->GetLevelScriptActor());
	if (IsValid(RifaGameInstance)) {
		if (RifaGameInstance->LevelSequencePlayerArr[ThisLevelSequenceIndex])
		{
			Destroy();
		}
	}

	if (LevelSequenceActor)
	{
		LevelSequence = LevelSequenceActor->LevelSequenceAsset;
		LevelSequencePlayer = LevelSequenceActor->SequencePlayer.Get();
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

void ABaseLevelSequencePlayActor::PlayLevelSequence()
{
	if (!RifaGameInstance->LevelSequencePlayerArr[ThisLevelSequenceIndex])
	{
		if (IsValid(CharacterReference) && IsValid(LevelSequencePlayer))
		{
			if (IsValid(CurrentLevelScriptActor))
			{
				if (IsValid(CurrentLevelScriptActor->GameHUDWidgetAsset))
				{
					CurrentLevelScriptActor->GameHUDWidgetAsset->CloseWidget();
				}
			}
			CharacterReference->DisableInput(Cast<APlayerController>(CharacterReference->Controller));
			FTimerHandle LevelSequenceTimer;
			FMovieSceneSequencePlaybackParams Param;
			LevelSequencePlayer->SetPlaybackPosition(Param);
			LevelSequencePlayer->Play();
			if (EndOfLevelSequencePlayerLocation != FVector(0, 0, 0))
			{
				CharacterReference->SetActorLocationAndRotation(EndOfLevelSequencePlayerLocation, EndOfLevelSequencePlayerRotation);
			}
			RifaGameInstance->LevelSequencePlayerArr[ThisLevelSequenceIndex] = true;
		}
	}
}

void ABaseLevelSequencePlayActor::EndLevelSequence()
{
	if (IsValid(CharacterReference)) {
		if (IsValid(CurrentLevelScriptActor->GameHUDWidgetClass))
		{
			CurrentLevelScriptActor->GameHUDWidgetAsset = Cast<UGameHUD>(CreateWidget(GetWorld(), CurrentLevelScriptActor->GameHUDWidgetClass));
			if (IsValid(CurrentLevelScriptActor->GameHUDWidgetAsset))
				CurrentLevelScriptActor->GameHUDWidgetAsset->Init();
		}
		CharacterReference->EnableInput(Cast<APlayerController>(CharacterReference->Controller));
		Cast<APlayerController>(CharacterReference->Controller)->SetInputMode(FInputModeGameOnly());
		Cast<APlayerController>(CharacterReference->Controller)->DefaultMouseCursor = EMouseCursor::Crosshairs;
		Destroy();
	}
}

