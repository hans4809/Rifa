// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MoveObj.generated.h"

UCLASS()
class RIFA_API AMoveObj : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMoveObj();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY()
	float timeDeltaTime;
	UPROPERTY()
		FVector startV;
	UPROPERTY()
		FVector endV;
	UPROPERTY()
		bool isFirst;

	UPROPERTY(EditAnywhere, Category = "Variable")
		float moveTime;
	UPROPERTY(EditAnywhere, Category = "Variable")
		float waitTime;
	UPROPERTY(EditAnywhere, Category = "ETC")
	USceneComponent* End;
	UPROPERTY(EditAnywhere, Category = "ETC")
	UStaticMeshComponent* Mesh;
	UPROPERTY()
	FTimerHandle fTimeHandler;

private:
	UFUNCTION()
		void BeginMove();
	UFUNCTION()
		void EndMove();
};
