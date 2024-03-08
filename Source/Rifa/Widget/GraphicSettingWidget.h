// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PopUpWidget.h"
#include "GraphicSettingWidget.generated.h"

/**
 * 
 */
UCLASS()
class RIFA_API UGraphicSettingWidget : public UPopUpWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* ReturnButton;
public:
	UFUNCTION(BlueprintCallable)
	void FirstConstruct();
	virtual void Init() override;
	virtual void CloseWidget() override;
};
