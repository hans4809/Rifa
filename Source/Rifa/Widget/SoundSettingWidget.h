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

// Widget Binding Section
protected:
	void NativeConstruct() override;
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UButton> CollectionButton;
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UButton> ReturnButton;
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class USlider> BGMSlider;
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class USlider> EnviromentalSlider;
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class USlider> SFXSlider;
// Reference Section
protected:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UPopUpWidget> CollectionWidgetClass;
	UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCollectionWidget> CollectionWidgetAsset;
// SoundClass Section
protected:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Sound", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USoundClass> BGMClass;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Sound", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USoundMix> BGMClassMix;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Sound", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USoundClass> EnviromentalClass;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Sound", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USoundMix> EnviromentalClassMix;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Sound", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USoundClass> SFXClass;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Sound", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USoundMix> SFXClassMix;
public:
	virtual void Init() override;
	virtual void CloseWidget() override;
	UFUNCTION(BlueprintCallable)
	void CollectionButtonClicked();
	UFUNCTION(BlueprintCallable)
	void BGMSliderValueChanged(float Value);
	UFUNCTION(BlueprintCallable)
	void EnviromentalSliderValueChanged(float Value);
	UFUNCTION(BlueprintCallable)
	void SFXSliderValueChanged(float Value);
};
