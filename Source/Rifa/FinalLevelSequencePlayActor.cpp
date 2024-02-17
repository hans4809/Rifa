// Fill out your copyright notice in the Description page of Project Settings.


#include "FinalLevelSequencePlayActor.h"

AFinalLevelSequencePlayActor::AFinalLevelSequencePlayActor()
{
}

void AFinalLevelSequencePlayActor::BeginPlay()
{
	Super::BeginPlay();
}

void AFinalLevelSequencePlayActor::PlayLevelSequence()
{
	Super::PlayLevelSequence();
}

void AFinalLevelSequencePlayActor::EndLevelSequence()
{
	Super::EndLevelSequence();
}

void AFinalLevelSequencePlayActor::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnCharacterOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

}

void AFinalLevelSequencePlayActor::EndCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::EndCharacterOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex);

}
