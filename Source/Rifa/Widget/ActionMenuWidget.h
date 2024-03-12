// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ActionMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class RIFA_API UActionMenuWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int InventorySlot;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	bool IsOn;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UButton> OnButton;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UButton> CancelButton;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	TObjectPtr<class UMyGameInstance> RifaGameInstance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	TObjectPtr<class USoundBase> InstSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	TObjectPtr<class UAudioComponent> InstAudioComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	TObjectPtr<class USoundConcurrency> InstSoundConcurrency;
	UFUNCTION(BlueprintCallable)
	void BGMOnButtonClicked();
	UFUNCTION(BlueprintCallable)
	void BGMOffButtonClicked();
	UFUNCTION(BlueprintCallable)
	void CancelButtonClicked();
protected:
	void NativeConstruct() override;
};
