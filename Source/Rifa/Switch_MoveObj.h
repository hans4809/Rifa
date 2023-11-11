// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Switch.h"
#include "Switch_MoveObj.generated.h"

UCLASS()
class RIFA_API ASwitch_MoveObj : public ASwitch
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
	UFUNCTION()
		void EndCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UPROPERTY(EditAnywhere, Category = "ETC")
		UStaticMeshComponent* Mesh;
	UPROPERTY(EditAnywhere, Category = "ETC")
		USceneComponent* End;
	UPROPERTY(EditAnywhere, Category = "ETC")
	class UBoxComponent* Trigger;

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

	UPROPERTY(EditAnywhere, Category = "Variable")
		float moveTime;
	UPROPERTY(EditAnywhere, Category = "Variable")
		AActor* Target;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void DoWork();
};