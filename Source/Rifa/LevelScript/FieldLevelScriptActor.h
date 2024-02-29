// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseLevelScriptActor.h"
#include "FieldLevelScriptActor.generated.h"

/**
 * 
 */
UCLASS()
class RIFA_API AFieldLevelScriptActor : public ABaseLevelScriptActor
{
	GENERATED_BODY()
public:
	AFieldLevelScriptActor();
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Reference")
	TObjectPtr<class ALevelSequenceActor> LevelSequenceActor;
private:
	virtual void BeginPlay() override;
protected:
	UFUNCTION()
	void OnFinishedLevelSequence();
};
