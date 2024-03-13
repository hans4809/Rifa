// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PopUpWidget.h"
#include "Data/MyGameInstance.h"
#include "TutorialWidget.generated.h"

/**
 * 
 */

UCLASS()
class RIFA_API UTutorialWidget : public UPopUpWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Type")
	ETutorialType ThisTutorialType = ETutorialType::Movement;
	virtual void Init() override;
	virtual void CloseWidget() override;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "LevelScript")
	TObjectPtr<class AIslandLevelScriptActor> IslandLevelScriptActor;
protected:
	void NativeConstruct() override;
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UImage> TutorialImage;
	UFUNCTION(BlueprintCallable)
	void ChangeImage();
};
