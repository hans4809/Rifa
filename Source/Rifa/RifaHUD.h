// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "RifaHUD.generated.h"

/**
 * 
 */
UCLASS()
class RIFA_API ARifaHUD : public AHUD
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	bool ShowCrossHair = true;
	void ReceiveDrawHUD(int32 SizeX, int32 SizeY);
};
