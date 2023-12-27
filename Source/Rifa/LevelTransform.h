// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelTransform.generated.h"

UCLASS()
class RIFA_API ALevelTransform : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ALevelTransform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
	UFUNCTION()
		void OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Variable")
		FString LevelName;
	UPROPERTY(EditAnywhere, Category = "ETC")
		class UBoxComponent* Trigger;

};
