// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseWidget.h"
#include "PopUpWidget.generated.h"

/**
 * 
 */
UCLASS()
class RIFA_API UPopUpWidget : public UBaseWidget
{
	GENERATED_BODY()
public:
	virtual void Init() override;
	virtual void CloseWidget() override;
};