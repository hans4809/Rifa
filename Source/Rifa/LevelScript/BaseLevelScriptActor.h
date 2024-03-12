// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "BaseLevelScriptActor.generated.h"

/**
 * 
 */
UCLASS()
class RIFA_API ABaseLevelScriptActor : public ALevelScriptActor
{
	GENERATED_BODY()
public:
	ABaseLevelScriptActor();
	UPROPERTY(BlueprintReadWrite, Category = "Widget")
	TObjectPtr<class UGameHUD> GameHUDWidgetAsset;
	UPROPERTY(BlueprintReadWrite, Category = "Widget")
	TSubclassOf<UUserWidget> GameHUDWidgetClass;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Sound")
	TObjectPtr<class AAmbientSound> BGM;
protected:
	virtual void BeginPlay() override;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> TutorialWidgetClass;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UTutorialWidget> TutorialWidgetAsset;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Reference", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class ARifaCharacter> CharacterReference;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Reference", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UMyGameInstance> RifaGameInstanceReference;
};
