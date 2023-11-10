// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/DataTable.h"
#include "MyGameInstance.generated.h"
/**
 * 
 */

USTRUCT()
struct FSavePointData : public FTableRowBase
{
	GENERATED_BODY()

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector Position;

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<int> ItemList;
};

struct FItemData;
class UDataTable;
UCLASS()
class RIFA_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UMyGameInstance();
	FItemData* GetItemData(int32 index);
private:
	UDataTable* ARifaDataTable;
};
