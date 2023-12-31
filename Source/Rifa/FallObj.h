// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FallObj.generated.h"

UCLASS()
class RIFA_API AFallObj : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFallObj();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void FallCount();

	UFUNCTION()
	void ResetObj();

	UPROPERTY()
	FTimerHandle fTimeHandler;

public:	
	UPROPERTY(EditAnywhere, Category="ETC")
	UStaticMeshComponent* Mesh;

	
	UPROPERTY(EditAnywhere, Category="Variable")
	float FallTime;

	UPROPERTY(EditAnywhere, Category="Variable")
	float RecoveryTime;

	UPROPERTY()
	bool isFall;

	UPROPERTY()
	FVector DefaultLocation;

	UPROPERTY()
	FRotator DefaultRotation;

private:
	UFUNCTION()
	virtual void NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;
};
