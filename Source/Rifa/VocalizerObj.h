// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "Containers/Queue.h"
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
	float timeDeltaTime_Sound;
	UPROPERTY()
	float timeDeltaTime_Vocalizer;

	UPROPERTY()
	float sphereScale;

	UPROPERTY()
	UStaticMesh* mesh;

	TQueue<UAudioComponent*> audioComponent;

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
	void SoundEnd();

	UFUNCTION()
	void OnCharacterOverlap_SoundZone(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void EndCharacterOverlap_SoundZone(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION()
	void OnCharacterOverlap_VocalizerVisibleZone(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void EndCharacterOverlap_VocalizerVisibleZone(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ETC")
	UStaticMeshComponent* staticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ETC")
	USphereComponent* triggerSphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ETC")
	USphereComponent* vocalizerSphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ETC")
	USphereComponent* vocalizerVisibleSphere;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ETC")
		bool isVocalizer;

	UPROPERTY()
	UWorld* world;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variable")
	float speed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Variable")
	float soundInterval;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Variable")
	float vocalizerInterval;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Variable")
	float maxOpacity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Variable")
	float minOpacity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variable")
	USoundBase* soundToPlay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variable")
	bool isPhysicCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Variable")
	FVector vocalizerColor;

	UPROPERTY()
	bool isActive;

	UPROPERTY()
	APawn* player;
};
