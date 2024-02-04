// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PopUpWidget.h"
#include "MyGameInstance.h"
#include "PickupText.generated.h"

/**
 * 
 */
UCLASS()
class RIFA_API UPickupText : public UPopUpWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Binding", meta = (AllowPrivateAccess = true))
	FString PickupText;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Actor", meta = (AllowPrivateAccess = true))
	AActor* PickupActor;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Location", meta = (AllowPrivateAccess = true))
	FVector ViewPortPosition;
	/*UPROPERTY(VisibleAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UImage> PressKeyImage;*/
	virtual void Init() override;
	virtual void CloseWidget() override;
private:
	void Tick(FGeometry MyGeometry, float InDeltaTime);
	virtual void NativeConstruct() override;
};
