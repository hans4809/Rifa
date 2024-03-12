// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LevelScript/BaseLevelScriptActor.h"
#include "MainMenuLevelScriptActor.generated.h"

/**
 * 
 */
UCLASS()
class RIFA_API AMainMenuLevelScriptActor : public ABaseLevelScriptActor
{
	GENERATED_BODY()
public:
	AMainMenuLevelScriptActor();
protected:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class USceneWidget> MainHUDWidgetClass;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class URifaMainHUD> MainHUDWidgetAsset;
	virtual void BeginPlay();
};
