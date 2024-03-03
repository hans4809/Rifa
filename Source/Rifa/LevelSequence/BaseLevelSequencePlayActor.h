// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseLevelSequencePlayActor.generated.h"


UENUM()
enum class ELevelSequenceType : uint8
{
	Trigger UMETA(DisplayName = "Trigger"),
	InterAction UMETA(DisplayName = "InterAction"),
	MaxCount
};
UCLASS()
class RIFA_API ABaseLevelSequencePlayActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseLevelSequencePlayActor();
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite)
	int32 ThisLevelSequenceIndex;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UBoxComponent> Trigger;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class ALevelSequenceActor> LevelSequenceActor;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class ULevelSequence> LevelSequence;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class ULevelSequencePlayer> LevelSequencePlayer;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class ARifaCharacter> CharacterReference;
	UFUNCTION(BlueprintCallable)
	virtual void OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UMyGameInstance> RifaGameInstance;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class ABaseLevelScriptActor> CurrentLevelScriptActor;
	UFUNCTION(BlueprintCallable)
	virtual void PlayLevelSequence();
	UFUNCTION(BlueprintCallable)
	virtual void EndLevelSequence();
};
