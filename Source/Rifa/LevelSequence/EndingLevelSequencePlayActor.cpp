// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelSequence/EndingLevelSequencePlayActor.h"
#include "Widget/EndingKeyWidget.h"
#include "Components/BoxComponent.h"
#include "LevelSequence/Public/LevelSequence.h"
#include "LevelSequence/Public/LevelSequencePlayer.h"
#include "LevelSequence/Public/LevelSequenceActor.h"
#include "Kismet/GameplayStatics.h"
#include "Character/RifaCharacter.h"
#include "Animation/SkeletalMeshActor.h"
#include "Data/MyGameInstance.h"
#include "Widget/GameHUD.h"
#include "LevelScript/FieldLevelScriptActor.h"

AEndingLevelSequencePlayActor::AEndingLevelSequencePlayActor()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> EndingKeyWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/BluePrint/UI/WG_EndingKeyWidget.WG_EndingKeyWidget_C'"));
	if(EndingKeyWidget.Succeeded())
	{
		EndingKeyWidgetClass = EndingKeyWidget.Class;
	}
	ThisLevelSequenceIndex = 9;
}

void AEndingLevelSequencePlayActor::BeginPlay()
{
	Super::BeginPlay();
	if (IsValid(EndingKeyWidgetClass))
	{
		EndingKeyWidgetAsset = CreateWidget<UEndingKeyWidget>(GetWorld(), EndingKeyWidgetClass);
	}
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AEndingLevelSequencePlayActor::OnCharacterOverlap);
}

void AEndingLevelSequencePlayActor::PlayLevelSequence()
{
	Super::PlayLevelSequence();
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
			GetWorld()->GetTimerManager().SetTimer(LevelSequenceTimer, this, &AEndingLevelSequencePlayActor::EndLevelSequence, LevelSequencePlayer->GetDuration().AsSeconds(), false);
			if (EndOfLevelSequencePlayerLocation != FVector(0, 0, 0))
			{
				CharacterReference->SetActorLocationAndRotation(EndOfLevelSequencePlayerLocation, EndOfLevelSequencePlayerRotation);
			}
			RifaGameInstance->LevelSequencePlayerArr[ThisLevelSequenceIndex] = true;
		}
	}
}

void AEndingLevelSequencePlayActor::EndLevelSequence()
{
	Super::EndLevelSequence();
	if (IsValid(CharacterReference)) {
		if (IsValid(CurrentLevelScriptActor->GameHUDWidgetAsset))
		{
			CurrentLevelScriptActor->GameHUDWidgetAsset->Init();
		}
		CharacterReference->EnableInput(Cast<APlayerController>(CharacterReference->Controller));
		if (EndingKeyWidgetAsset) 
		{
			EndingKeyWidgetAsset->Init();
		}
	}
}

void AEndingLevelSequencePlayActor::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnCharacterOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	if(Cast<ARifaCharacter>(OtherActor))
	{
		PlayLevelSequence();
	}
}
