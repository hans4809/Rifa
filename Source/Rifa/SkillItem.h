// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableActor.h"
#include "SkillItem.generated.h"

/**
 * 
 */
UENUM()
enum class EEnergyType : uint8
{
	Swim UMETA(DisplayName = "Swim"),
	Fly UMETA(DisplayName = "Fly")
};
UCLASS()
class RIFA_API ASkillItem : public AInteractableActor
{
	GENERATED_BODY()
public:
	ASkillItem();
// Component Section
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UNiagaraComponent> Particle;	
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = Data, meta = (AllowPrivateAccess = "true"))
	int32 ThisSkillItemIndex;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = Data, meta = (AllowPrivateAccess = "true"))
	EEnergyType ThisEnergyType;
	UFUNCTION(BlueprintCallable)
	void PickupEnergyEvent();
// Tutorial Section
private:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> TutorialWidgetClass;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UTutorialWidget> TutorialWidgetAsset;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "LevelSequence", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class ALevelSequenceActor> LevelSequenceActor;
	UFUNCTION()
	void EndLevelSequence();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
