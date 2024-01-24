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
	void PlayerRespawn(class ARifaCharacter* Player);
protected:
	/*UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> GameHUDWidgetClass;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	class UGameHUD* GameHUDWidget;*/
	virtual void BeginPlay();
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Reference")
	TObjectPtr<class ARifaCharacter> CharacterReference;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Reference")
	TObjectPtr<class UMyGameInstance> GameInstanceReference;
};



