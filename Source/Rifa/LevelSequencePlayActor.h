// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelSequencePlayActor.generated.h"

UCLASS()
class RIFA_API ALevelSequencePlayActor : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	ALevelSequencePlayActor();
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	class ASkeletalMeshActor* CharacterMesh;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* Trigger;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class ALevelSequenceActor* LevelSequenceActor;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class ULevelSequence* LevelSequnce;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class ULevelSequencePlayer* LevelSequencePlayer;
	UPROPERTY()
	FTimerHandle LevelSequenceTimer;
	UFUNCTION(BlueprintCallable)
	void EndLevelSequence();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
};
