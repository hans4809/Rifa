// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/SceneWidget.h"
#include "EndingKeyWidget.generated.h"

/**
 * 
 */
UCLASS()
class RIFA_API UEndingKeyWidget : public USceneWidget
{
	GENERATED_BODY()
public:
	UEndingKeyWidget(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "LevelSequence")
	TObjectPtr<class ULevelSequence> EndingLevelSequence;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "LevelSequence")
	TObjectPtr<class ULevelSequencePlayer> EndingLevelSequencePlayer;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "LevelSequence")
	class ALevelSequenceActor* EndingLevelSequenceActor;

protected:
	void NativeConstruct() override;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	UFUNCTION(BlueprintCallable)
	void PlayEndingLevelSequence();
};
