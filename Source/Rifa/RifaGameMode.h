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
	void PlayerDie();
protected:
	/*UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> GameHUDWidgetClass;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	class UGameHUD* GameHUDWidget;*/
	virtual void BeginPlay();
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Catergory = "Reference")
	TObjectPtr<class ARifaCharacter> CharacterReference;
};



