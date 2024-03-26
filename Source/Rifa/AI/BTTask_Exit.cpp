// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_Exit.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Character/NPCAIController.h"
#include "Widget/DialogWidget.h"
#include "Widget/DialogComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BTNode.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"

UBTTask_Exit::UBTTask_Exit()
{
	DialogWidget.SelectedKeyName = TEXT("DialogWidget");
	DialogWidget.SelectedKeyType = UDialogWidget::StaticClass();
}

EBTNodeResult::Type UBTTask_Exit::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	if (ControllingPawn == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	UDialogWidget* DialogWidgetAsset = Cast<UDialogWidget>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(DialogWidget.SelectedKeyName));
	if (DialogWidgetAsset == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	DialogWidgetAsset->Exit_C();
	Result = EBTNodeResult::Succeeded;


	return Result;
}
