// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InventoryStruct.generated.h"

UCLASS()
class RIFA_API AInventoryStruct : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInventoryStruct();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
USTRUCT(Atomic, BlueprintType)
struct FItemStruct
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	AActor* Item;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	UTexture2D* ItemImage;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FString ItemName;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FString AcitonText;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	bool BGM_On;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	bool IsHave;
};


