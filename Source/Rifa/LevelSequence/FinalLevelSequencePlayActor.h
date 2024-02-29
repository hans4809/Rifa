// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseLevelSequencePlayActor.h"
#include "FinalLevelSequencePlayActor.generated.h"

/**
 * 
 */
UCLASS()
class RIFA_API AFinalLevelSequencePlayActor : public ABaseLevelSequencePlayActor
{
	GENERATED_BODY()
public:
	AFinalLevelSequencePlayActor();

private:

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PlayLevelSequence() override;
	virtual void EndLevelSequence() override;
	virtual void OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	virtual void EndCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;
};
