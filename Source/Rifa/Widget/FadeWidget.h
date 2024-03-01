// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/SceneWidget.h"
#include "FadeWidget.generated.h"

/**
 * 
 */
UCLASS()
class RIFA_API UFadeWidget : public USceneWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Transient, Category = "GsUI", meta = (BindWidgetAnim))
	TObjectPtr<class UWidgetAnimation> FadeIn;
	UPROPERTY(BlueprintReadWrite, Transient, Category = "GsUI", meta = (BindWidgetAnim))
	TObjectPtr<class UWidgetAnimation> FadeOut;
private:
protected:
	virtual void NativeConstruct() override;
	FWidgetAnimationDynamicEvent StartDelegate;
	FWidgetAnimationDynamicEvent EndDelegate;
	UFUNCTION()
	void AnimationFinished();
};
