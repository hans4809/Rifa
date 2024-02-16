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
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> GameHUDWidgetClass;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	TObjectPtr<class UGameHUD> GameHUDWidgetAsset;
protected:
	virtual void BeginPlay();
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Reference")
	TObjectPtr<class ARifaCharacter> CharacterReference;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Reference")
	TObjectPtr<class UMyGameInstance> GameInstanceReference;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Reference", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class ALevelSequenceActor> FirstLevelSequence;
	UFUNCTION()
	void EndLevelSequence();
};



