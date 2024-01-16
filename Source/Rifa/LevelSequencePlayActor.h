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
	TObjectPtr<class ALevelSequenceCharacterActor> CharacterMesh;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* Trigger;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class ALevelSequenceActor* LevelSequenceActor;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class ULevelSequence* LevelSequence;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class ULevelSequencePlayer* LevelSequencePlayer;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class ARifaCharacter* CharacterReference;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FVector EndOfLevelSequencePlayerLocation;
	UPROPERTY()
	FTimerHandle LevelSequenceTimer;
	UFUNCTION(BlueprintCallable)
	void EndLevelSequence();
	UFUNCTION(BlueprintCallable)
	void OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
