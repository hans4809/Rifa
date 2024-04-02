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
#include "Character/RifaNPC.h"
#include "Data/MyGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Components/WidgetComponent.h"

UBTTask_Exit::UBTTask_Exit()
{
	DialogWidget.SelectedKeyName = TEXT("DialogWidget");
	DialogWidget.SelectedKeyType = UDialogWidget::StaticClass();
}

EBTNodeResult::Type UBTTask_Exit::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	ARifaNPC* ControllingPawn = Cast<ARifaNPC>(OwnerComp.GetAIOwner()->GetPawn());
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

	if (UMyGameInstance* GameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld())))
	{
		GameInstance->NPCDialogMap[ControllingPawn->ThisNPCType]++;
		ControllingPawn->GetWidgetComponent()->SetVisibility(true);
	}

	Result = EBTNodeResult::Succeeded;

	return Result;
}
