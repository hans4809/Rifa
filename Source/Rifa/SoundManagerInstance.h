// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SoundManagerInstance.generated.h"

/**
 * 
 */
UCLASS()
class RIFA_API USoundManagerInstance : public UGameInstanceSubsystem
{
	GENERATED_BODY()
private:
	USoundManagerInstance();
public:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	class UAudioComponent* BGMSound;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	class UAudioComponent* SFXSound;
};
