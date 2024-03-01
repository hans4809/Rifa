// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryStruct.h"
#include "InventorySlot.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDele_Dynamic_OneParam, int32, InValue);
UCLASS()
class RIFA_API UInventorySlot : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "Event")
	FDele_Dynamic_OneParam ButtonWasClicked;
	UFUNCTION(BlueprintCallable)
	void ButtonWasClicked_Event();
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	TObjectPtr<UTexture2D> HavingImage;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	TObjectPtr<UTexture2D> DefaultImage;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	int InventorySlot;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UButton> ItemButton;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SlotData, meta = (AllowPrivateAccess = "true"))
	bool IsHave;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SlotData, meta = (AllowPrivateAccess = "true"))
	bool BGM_On;
protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
};
