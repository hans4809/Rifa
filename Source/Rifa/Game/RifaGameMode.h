// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RifaGameMode.generated.h"

UCLASS(minimalapi)
class ARifaGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ARifaGameMode();
	UFUNCTION(BlueprintCallable)
	void PlayerDie(class ARifaCharacter* Player);
	UFUNCTION(BlueprintCallable)
	void PlayerRespawn();
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = Widget)
	TSubclassOf<UUserWidget> GameHUDWidgetClass;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = Widget)
	TObjectPtr<class UGameHUD> GameHUDWidgetAsset;
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Widget)
	TSubclassOf<class UUserWidget> FadeWidgetClass;
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Widget)
	TObjectPtr<class UFadeWidget> FadeWidgetReference;
protected:
	virtual void BeginPlay();
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Reference")
	TObjectPtr<class ARifaCharacter> CharacterReference;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Reference")
	TObjectPtr<class UMyGameInstance> GameInstanceReference;
};



