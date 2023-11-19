// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PopUpWidget.h"
#include "SoundSettingWidget.generated.h"

/**
 * 
 */
UCLASS()
class RIFA_API USoundSettingWidget : public UPopUpWidget
{
	GENERATED_BODY()
protected:
	void NativeConstruct() override;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* CollectionButton;
	//UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	//class UButton* ControlButton;
	//UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	//class UButton* ReturnButton;

public:
	UFUNCTION(BlueprintCallable)
	virtual void Init() override;
	UFUNCTION(BlueprintCallable)
	virtual void CloseWidget() override;
	UFUNCTION(BlueprintCallable)
	void CrossFadeSound();	
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Sound", meta = (AllowPrivateAccess = "true"))
	UAudioComponent* BGMComponent;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Sound", meta = (AllowPrivateAccess = "true"))
	float AudioParam = 0.f;
};
