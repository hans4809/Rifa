// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WaterActor.h"
#include "FlowWaterActor.generated.h"

/**
 * 
 */
UCLASS()
class RIFA_API AFlowWaterActor : public AWaterActor
{
	GENERATED_BODY()
public:
	AFlowWaterActor();
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	TObjectPtr<class UArrowComponent> ArrowComponent;
private:
	void OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
};
