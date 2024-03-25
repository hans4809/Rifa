// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Exit.generated.h"

/**
 * 
 */
UCLASS()
class RIFA_API UBTTask_Exit : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTask_Exit();
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector DialogWidget;
private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
