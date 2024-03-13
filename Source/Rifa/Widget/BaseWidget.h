// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BaseWidget.generated.h"

/**
 * 
 */
UCLASS()
class RIFA_API UBaseWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	virtual void Init();
	UFUNCTION(BlueprintCallable)
	virtual void CloseWidget();
	UPROPERTY(BlueprintReadWrite, category = "LevelScript")
	TObjectPtr<class ABaseLevelScriptActor> CurrentLevelScriptActor;
	UPROPERTY(BlueprintReadWrite, category = "GameInstnace")
	TObjectPtr<class UMyGameInstance> RifaGameInstance;
};
