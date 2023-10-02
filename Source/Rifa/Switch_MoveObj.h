// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Switch_MoveObj.generated.h"

UCLASS()
class RIFA_API ASwitch_MoveObj : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASwitch_MoveObj();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void PostInitializeComponents() override;

private:
	UFUNCTION()
		void OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UPROPERTY(EditAnywhere, Category = "Switch_MoveObj")
		UStaticMeshComponent* Mesh;
	UPROPERTY(EditAnywhere, Category = "Switch_MoveObj")
		USceneComponent* End;
	UPROPERTY()
		FTimerHandle fTimeHandler;
	UFUNCTION()
		void BeginMove();
	UPROPERTY()
		float timeDeltaTime;
	UPROPERTY()
		FVector startV;
	UPROPERTY()
		FVector endV;
	UPROPERTY()
		bool isStart;

	UPROPERTY(EditAnywhere, Category = "MoveObj")
		float moveTime;
	UPROPERTY(EditAnywhere, Category = "MoveObj")
		AActor* Target;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UBoxComponent* Trigger;
};
