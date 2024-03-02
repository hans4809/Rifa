// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/PopUpWidget.h"
#include "FadeWidget.generated.h"

/**
 * 
 */
UCLASS()
class RIFA_API UFadeWidget : public UPopUpWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, Transient, Category = "Animation", meta = (BindWidgetAnim))
	TObjectPtr<class UWidgetAnimation> FadeIn;
	UPROPERTY(BlueprintReadWrite, Transient, Category = "Animation", meta = (BindWidgetAnim))
	TObjectPtr<class UWidgetAnimation> FadeOut;
private:
protected:
	virtual void NativeConstruct() override;
	FWidgetAnimationDynamicEvent EndDelegate;
	UFUNCTION()
	void AnimationFinished();
};
