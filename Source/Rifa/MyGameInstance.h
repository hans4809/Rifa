// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"
/**
 * 
 */
UENUM()
enum class UI_Name : uint8
{
	UPanelWidget UMETA(DisplayName = "UPanelWidget")
};

UENUM()
enum class Item : uint8
{
	Piano_1_Medium,
	WindInstrument_1_Medium,
	Bell_1_High,
	Voice_1_Women,
	Piano_1_High,
	StringInstrument_1_Medium,
	Piano_2_Low,
	WindInstrument_2_Medium,
	Voice_2_Men,
	PercussionInstrument_1_Low,
	StringInstrument_2_Medium,
	Piano_2_High,
	StringInstrument_3_High,
	Bell_2_High,
	PercussionInstrument_3_High,
	StringInstrument_4_High,
	MaxCount
};

UCLASS()
class RIFA_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UMyGameInstance();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Position;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString SoundTrack;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap <Item, bool> ItemMap;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int PopupSort = 5;

	UFUNCTION()
	void Save();

	UFUNCTION()
	void Load();
	virtual void Init() override;
};
