// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelSequencePlayActor.generated.h"
UENUM()
enum class ELevelSequenceType : uint8
{
	Trigger UMETA(DisplayName = "Trigger"),
	InterAction UMETA(DisplayName = "InterAction"),
	MaxCount
};
UCLASS()
class RIFA_API ALevelSequencePlayActor : public AActor
{
	GENERATED_BODY()

public:	
	// Sets default values for this actor's properties
	ALevelSequencePlayActor();
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	bool bCanPlayLevelSequence;
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
	ELevelSequenceType ThisLevelSequenceType;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FVector EndOfLevelSequencePlayerLocation;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class ARifaCharacter> CharacterReference;
	UPROPERTY()
	FTimerHandle LevelSequenceTimer; 
	UFUNCTION(BlueprintCallable)
	void PlayLevelSequence();
	UFUNCTION(BlueprintCallable)
	void EndLevelSequence();
	UFUNCTION(BlueprintCallable)
	void OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION(BlueprintCallable)
	void EndCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UMyGameInstance> RifaGameInstance;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
