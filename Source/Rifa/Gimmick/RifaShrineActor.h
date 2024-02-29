// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RifaShrineActor.generated.h"

UCLASS()
class RIFA_API ARifaShrineActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARifaShrineActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* ShrinePart1;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* ShrinePart2;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* ShrinePart3;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* ShrinePart4;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* Rock;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* Wood;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
