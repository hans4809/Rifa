// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/PopUpWidget.h"
#include "WaterFallWidget.generated.h"

/**
 * 
 */
UCLASS()
class RIFA_API UWaterFallWidget : public UBaseWidget
{
	GENERATED_BODY()
public:
	virtual void Init() override;
	virtual void CloseWidget() override;
};
