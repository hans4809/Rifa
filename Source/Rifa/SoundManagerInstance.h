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
	class UAudioComponent* BGMSound1;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	class UAudioComponent* BGMSound2;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	class UAudioComponent* SFXSound;

	UFUNCTION()
		void PlayBGM(USoundBase* soundToPlay, TArray <bool> checkArray);
	UFUNCTION()
	void PlaySFX(USoundBase* soundToPlay);
private:
	UPROPERTY()
		bool isPlayBGM;
	UPROPERTY()
	bool crruentPlayBGMAudioIndex;
};
