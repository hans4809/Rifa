// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "BaseLevelScriptActor.generated.h"

/**
 * 
 */
UCLASS()
class RIFA_API ABaseLevelScriptActor : public ALevelScriptActor
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Reference")
	TArray<TObjectPtr<AActor>> LevelSequenceCharacterArr;
protected:
	virtual void BeginPlay() override;
};
