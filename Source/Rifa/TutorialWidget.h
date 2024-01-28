// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PopUpWidget.h"
#include "MyGameInstance.h"
#include "TutorialWidget.generated.h"

/**
 * 
 */

UCLASS()
class RIFA_API UTutorialWidget : public UPopUpWidget
{
	GENERATED_BODY()
public:
	ETutorialType ThisTutorialType = ETutorialType::Movement;
protected:
	void NativeConstruct() override;
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UImage> TutorialImage;
};
