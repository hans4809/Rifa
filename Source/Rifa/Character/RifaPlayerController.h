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
	virtual void PostInitializeComponents() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> GameHUDWidgetClass;

private:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UUserWidget> CreditWidgetClass;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCreditWidget> CreditWidgetAsset;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UGameHUD> GameHUDWidgetAsset;

	UFUNCTION()
	void OnStartedLevelSequence();

	UFUNCTION()
	void OnFinishedLevelSequence();

	UFUNCTION()
	void OnFinishedGame();
};
