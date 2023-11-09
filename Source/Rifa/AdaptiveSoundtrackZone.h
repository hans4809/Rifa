// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AdaptiveSoundtrackZone.generated.h"

UCLASS()
class RIFA_API AAdaptiveSoundtrackZone : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAdaptiveSoundtrackZone();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

	UFUNCTION()
		void OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* Trigger;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SoundTrack")
	FString SoundTrack;
};