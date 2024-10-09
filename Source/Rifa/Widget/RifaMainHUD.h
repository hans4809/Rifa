// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SceneWidget.h"
#include "RifaMainHUD.generated.h"

/**
 * 
 */
UCLASS()
class RIFA_API URifaMainHUD : public USceneWidget
{
	GENERATED_BODY()
public:
	URifaMainHUD(const FObjectInitializer &ObjectInitializer);
protected:
	void NativeConstruct() override;

protected:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* TranslateButton;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* ResetButton;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* LoadButton;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* SettingButton;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* QuitButton;
public:
	virtual void Init() override;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UPopUpWidget> MainSettingWidgetClass;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	class UMainSettingWidget* MainSettingWidgetAsset;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UPopUpWidget> ResetDataQuestionWidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UResetDataQuestionWidget> ResetDataQuestionWidgetAsset;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Sound", meta = (AllowPrivateAccess = "true"))
	class USoundCue* MainBGM;
private:
	UFUNCTION(BlueprintCallable)
	void SettingButtonClicked();
	UFUNCTION(BlueprintCallable)
	void LoadButtonClicked();
	UFUNCTION(BlueprintCallable)
	void ResetButtonClicked();
	UFUNCTION(BlueprintCallable)
	void QuitButtonClicked();
	UFUNCTION(BlueprintCallable)
	void TranslateButtonClicked();
};
