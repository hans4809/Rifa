// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LevelSequence/BaseLevelSequencePlayActor.h"
#include "EndingLevelSequencePlayActor.generated.h"

/**
 * 
 */
UCLASS()
class RIFA_API AEndingLevelSequencePlayActor : public ABaseLevelSequencePlayActor
{
	GENERATED_BODY()
public:
	AEndingLevelSequencePlayActor();
private:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UUserWidget> EndingKeyWidgetClass;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UEndingKeyWidget> EndingKeyWidgetAsset;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FVector EndOfLevelSequencePlayerLocation = FVector::Zero();
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FRotator EndOfLevelSequencePlayerRotation = FRotator::ZeroRotator;
	virtual void PlayLevelSequence() override;
	virtual void EndLevelSequence() override;
	virtual void OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
};
