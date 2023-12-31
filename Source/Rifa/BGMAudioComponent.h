// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MyGameInstance.h"
#include "BGMAudioComponent.generated.h"

/**
 * 
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RIFA_API UBGMAudioComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UBGMAudioComponent();
	
protected:

public:
	UPROPERTY(EditAnywhere)
	UAudioComponent* BgmAudioPrevious;
	UPROPERTY(EditAnywhere)
	UAudioComponent* BgmAudioNew;
	UPROPERTY()
	float CrossfadeDuration;
	UPROPERTY(EditAnyWhere)
	class UMyGameInstance* RifaGameInstance;
	UPROPERTY()
	TArray<Item> CheckArray;
	UPROPERTY()
	USoundBase* SoundToPlay;
	UPROPERTY(EditAnywhere)
	TArray<USoundBase*> Sounds;
	UPROPERTY()
		FString Str;

	UFUNCTION()
	void CrossfadeSound();
	UFUNCTION()
	void PlayBgm();
	UFUNCTION()
	void BgmSetting();
};