// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseLevelScriptActor.h"
#include "IslandLevelScriptActor.generated.h"

/**
 * 
 */
UCLASS()
class RIFA_API AIslandLevelScriptActor : public ABaseLevelScriptActor
{
	GENERATED_BODY()
//Level Sequence Section
public:
	AIslandLevelScriptActor();

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Reference")
	TObjectPtr<class ALevelSequenceActor> FirstLevelSequenceActor;
//Widget Section
protected:

protected:
	virtual void BeginPlay() override;
	UFUNCTION()
	void OnFinishedFirstLevelSequence();
	virtual void Tick(float DeltaTime) override;
};
