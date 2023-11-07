// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PickupText.generated.h"

/**
 * 
 */
UCLASS()
class RIFA_API UPickupText : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Binding", meta = (AllowPrivateAccess = true))
	FString PickupText;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Actor", meta = (AllowPrivateAccess = true))
	AActor* PickupActor;
};
