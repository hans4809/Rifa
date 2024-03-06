// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/PopUpWidget.h"
#include "EndingKeyWidget.generated.h"

/**
 * 
 */
UCLASS()
class RIFA_API UEndingKeyWidget : public UPopUpWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "LevelSequence")
	TObjectPtr<class ULevelSequence> EndingLevelSequence;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "LevelSequence")
	TObjectPtr<class ULevelSequencePlayer> EndingLevelSequencePlayer;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "LevelSequence")
	class ALevelSequenceActor* EndingLevelSequenceActor;
protected:
	void NativeConstruct() override;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Reference", meta = (AllowPrivateAccess = true))
	TObjectPtr<class ARifaCharacter> CharacterReference;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Reference", meta = (AllowPrivateAccess = true))
	TObjectPtr<class UMyGameInstance> RifaGameInstance;
	UFUNCTION(BlueprintCallable)
	void PlayEndingLevelSequence();
	UFUNCTION(BlueprintCallable)
	void EndEndingLevelSequence();
};
