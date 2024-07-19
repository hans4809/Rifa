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

}

void AEndingLevelSequencePlayActor::BeginPlay()
{
	Super::BeginPlay();
	if (IsValid(EndingKeyWidgetClass))
		EndingKeyWidgetAsset = CreateWidget<UEndingKeyWidget>(GetWorld(), EndingKeyWidgetClass);

	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AEndingLevelSequencePlayActor::OnCharacterOverlap);
}

void AEndingLevelSequencePlayActor::PlayLevelSequence()
{
	Super::PlayLevelSequence();

	FTimerHandle LevelSequenceTimer;
	GetWorld()->GetTimerManager().SetTimer(LevelSequenceTimer, this, &AEndingLevelSequencePlayActor::EndLevelSequence, LevelSequencePlayer->GetDuration().AsSeconds(), false);
}

void AEndingLevelSequencePlayActor::EndLevelSequence()
{
	Super::EndLevelSequence();

	if (EndingKeyWidgetAsset) 
		EndingKeyWidgetAsset->Init();
}

void AEndingLevelSequencePlayActor::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnCharacterOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	if(Cast<ARifaCharacter>(OtherActor))
		PlayLevelSequence();
}
