// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Speak.generated.h"

/**
 * 
 */
UCLASS()
class RIFA_API UBTTask_Speak : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTask_Speak();
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector DialogWidget;
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FText SpeakText;
	UFUNCTION()
	void OnSpeakFinished_Evt();
private:
	UPROPERTY()
	TObjectPtr<class UBehaviorTreeComponent> OwnerCompRef;
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
