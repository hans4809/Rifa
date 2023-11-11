// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "RifaDataTable.generated.h"

USTRUCT(BlueprintType)
struct FItemData : public FTableRowBase
{
	GENERATED_BODY()

public:
	FItemData() : ItemNum(1), ItemName("피아노1_중음"), Instrument("클래식"), Position("섬 (초반부)"), BGM_1(true), BGM_2(false), BGM_3(true), BGM_4(false), BGM_5(false), BGM_6(true), BGM_7(false), BGM_8(false)  {}
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	int ItemNum;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString ItemName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString Instrument;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	FString Position;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	bool BGM_1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	bool BGM_2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	bool BGM_3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	bool BGM_4;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	bool BGM_5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	bool BGM_6;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	bool BGM_7;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
	bool BGM_8;
};
UCLASS()
class RIFA_API ARifaDataTable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARifaDataTable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
