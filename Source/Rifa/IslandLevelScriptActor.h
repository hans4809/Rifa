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
public:

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Reference")
	TObjectPtr<class ARifaCharacter> CharacterReference;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Reference")
	TObjectPtr<class UMyGameInstance> RifaGameInstanceReference;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Reference")
	TObjectPtr<class ALevelSequenceActor> FirstLevelSequenceActor;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Reference")
	TObjectPtr<class ALevelSequenceCharacterActor> FirstLevelSequenceCharacterActor;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Reference")
	TObjectPtr<class ALevelSequenceActor> SecondLevelSequenceActor;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Reference")
	FTimerHandle SequenceTimer;
protected:
	virtual void BeginPlay() override;
	UFUNCTION()
	void OnFinishedFirstLevelSequence();
	UFUNCTION()
	void OnFinishedSecondLevelSequence();
};
