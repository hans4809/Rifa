// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Reply.generated.h"

/**
 * 
 */
UCLASS()
class RIFA_API UBTTask_Reply : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector DialogWidget;
};
