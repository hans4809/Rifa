// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Vocalizer.generated.h"

UCLASS()
class RIFA_API AVocalizer : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVocalizer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	UStaticMeshComponent* staticMesh;

	UPROPERTY()
	FVector vocalizerColor;

	UPROPERTY()
	bool isStart;

	UPROPERTY()
	float maxSize;

	UPROPERTY()
	float speed;

	UPROPERTY()
	float scale;

	UPROPERTY()
	float maxOpacity;

	UPROPERTY()
	float minOpacity;

	UFUNCTION()
	void MoveStart();

	UFUNCTION()
	void Move();
};
