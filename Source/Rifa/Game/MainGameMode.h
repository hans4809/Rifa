// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "MainGameMode.generated.h"

/**
 * 
 */
UCLASS()
class RIFA_API AMainGameMode : public AGameMode
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class USceneWidget> MainHUDWidgetClass;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	class URifaMainHUD* MainHUDWidgetAsset;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Sound", meta = (AllowPrivateAccess = "true"))
	UAudioComponent* BGM;
protected:
	virtual void BeginPlay();
};
