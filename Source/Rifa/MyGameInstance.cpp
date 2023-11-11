// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "RifaGameMode.h"
#include "RifaDataTable.h"

UMyGameInstance::UMyGameInstance()
{
	for (int i = 0; i < (int)Item::MaxCount; i++) {
		ItemMap.Add((Item)i, false);
	}
}

