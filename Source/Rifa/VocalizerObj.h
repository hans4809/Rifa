// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "VocalizerObj.generated.h"

UCLASS()
class RIFA_API AVocalizerObj : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVocalizerObj();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

	UPROPERTY()
	float sphereRadius;

	UPROPERTY()
	float soundDuration;

	UPROPERTY()
	float timeDeltaTime;

	UPROPERTY()
	float sphereScale;

	UPROPERTY()
	UStaticMesh* mesh;

	UFUNCTION()
	void TimeCheck();

	UFUNCTION()
	void SoundPlay();

	UFUNCTION()
	void SoundWave();

	UFUNCTION()
	void SoundOn();

	UFUNCTION()
	void SoundOff();

	UFUNCTION()
	void OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void EndCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "sound")
	USoundBase* soundToPlay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	UStaticMeshComponent* staticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	USphereComponent* triggerSphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	USphereComponent* vocalizerSphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	USphereComponent* vocalizerVisibleSphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "sound")
	bool isPhysicCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "sound")
	FVector vocalizerColor;

	UPROPERTY()
	UWorld* world;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "sound")
	float speed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "sound")
	float soundInterval;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "sound")
	float maxOpacity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "sound")
	float minOpacity;

	UPROPERTY()
	float volumeSize;

	UPROPERTY()
	bool isActive;

	UPROPERTY()
	APawn* player;
};
