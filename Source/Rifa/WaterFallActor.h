// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WaterFallActor.generated.h"

UCLASS()
class RIFA_API AWaterFallActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWaterFallActor();
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "WaterFall", meta = (AllowPrivateAccess = "true"))
	class USceneComponent* Root;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "WaterFall", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Mesh;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "WaterFall", meta = (AllowPrivateAccess = "true"))
	class UNiagaraComponent* WaterFall;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
