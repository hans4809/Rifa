// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "RifaGameMode.h"
#include "RifaDataTable.h"

UMyGameInstance::UMyGameInstance()
{
	FString ItemDataPath = TEXT("/Script/Engine.DataTable'/Game/ItemDataTable.ItemDataTable'");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_ARifaData(*ItemDataPath);
	if (DT_ARifaData.Succeeded())
	{
		ARifaDataTable = DT_ARifaData.Object;
	}
}

FItemData* UMyGameInstance::GetItemData(int32 index)
{
	return ARifaDataTable->FindRow<FItemData>(*FString::FromInt(index), TEXT(""));
}
