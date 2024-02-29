// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableActor.h"
#include "SkillItem.h"
#include "ShrinItem.generated.h"

/**
 * 
 */
UCLASS()
class RIFA_API AShrinItem : public AInteractableActor
{
	GENERATED_BODY()
public:
	AShrinItem();
private:
	virtual void BeginPlay() override;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Particle, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UNiagaraComponent> Particle;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = Data, meta = (AllowPrivateAccess = "true"))
	EEnergyType ThisEnergyType;
	UFUNCTION(BlueprintCallable)
	void PickupShrineItem();
protected:
};
