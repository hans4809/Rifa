// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LevelSequencePlayActor.h"
#include "Items/SkillItem.h"
#include "FinalLevelSequencePlayActor.generated.h"

/**
 * 
 */
UCLASS()
class RIFA_API AFinalLevelSequencePlayActor : public ALevelSequencePlayActor
{
	GENERATED_BODY()
public:
	AFinalLevelSequencePlayActor();

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UStaticMeshComponent> Mesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Particle, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UNiagaraComponent> Particle;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	EEnergyType ThisEnergyType;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PlayLevelSequence() override;
	virtual void EndLevelSequence() override;
	virtual void OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
};
