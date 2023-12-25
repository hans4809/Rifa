// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WorldLightChange.generated.h"

UCLASS()
class RIFA_API AWorldLightChange : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWorldLightChange();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* Trigger;
	UPROPERTY(EditAnywhere, Category = "Etc")
	USceneComponent* end;

	UPROPERTY(EditAnywhere, Category = "Variable")
		float StartDegree;
	UPROPERTY(EditAnywhere, Category = "Variable")
		float EndDegree;

	UPROPERTY()
		bool IsChangeStart;

	UPROPERTY()
		AActor* player;

	UPROPERTY()
		float MaxDistance;

	UPROPERTY()
		float Distance;

	UPROPERTY(EditAnywhere)
		AActor* light;
		
	UPROPERTY(EditAnywhere)
		FRotator lightDefault;
};
