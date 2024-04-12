// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WaterFall.generated.h"

UCLASS()
class RIFA_API AWaterFall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWaterFall();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "WaterFall", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UStaticMeshComponent> Mesh;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "WaterFall", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UAudioComponent> Sound;	
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "WaterFall", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UNiagaraComponent> WaterFall;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
