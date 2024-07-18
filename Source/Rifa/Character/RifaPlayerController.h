// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "RifaPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class RIFA_API ARifaPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	ARifaPlayerController();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> GameHUDWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UGameHUD> GameHUDWidgetAsset;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
