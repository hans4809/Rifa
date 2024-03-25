// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Reply.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class RIFA_API UBTTask_Reply : public UBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTask_Reply();
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector DialogWidget;
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	TArray<FText> Replies;
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector OutReplyIndex;
protected:
	//Task 실행 함수 오버라이딩
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	UPROPERTY()
	TObjectPtr<class UBehaviorTreeComponent> OwnerCompRef;
private:
	UFUNCTION()
	void OnReplyFinished_Evt(int32 Index);
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	TObjectPtr<class ANPCAIController> AIController;
};
