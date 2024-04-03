// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogComponent.h"
#include <Kismet/GameplayStatics.h>
#include "DialogWidget.h"
#include "Character/NPCAIController.h"
#include "BrainComponent.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Character/RifaNPC.h"
#include "Data/MyGameInstance.h"

// Sets default values for this component's properties
UDialogComponent::UDialogComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT("/Script/AIModule.BlackboardData'/Game/BluePrint/UI/DialogSystem/DialogBlackBoard.DialogBlackBoard'"));
	if (BBObject.Succeeded())
	{
		DialogBlackBoard = BBObject.Object;
	}

	// ...
}


// Called when the game starts
void UDialogComponent::BeginPlay()
{
	Super::BeginPlay();
	DialogAIController = Cast<ANPCAIController>(GetWorld()->SpawnActor(ANPCAIController::StaticClass()));
	DialogAIController->SetPawn(Cast<APawn>(GetOwner()));
	// ...
	if (IsValid(DialogWidgetClass))
	{
		DialogWidgetAsset = Cast<UDialogWidget>(CreateWidget(GetWorld(), DialogWidgetClass));
	}
	DialogWidgetAsset->OnExit.AddDynamic(this, &UDialogComponent::OnExit);
}


// Called every frame
void UDialogComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UDialogComponent::OnInterAction(ARifaCharacter* InterActionCharacter)
{
	DialogAIController->RunBehaviorTree(DialogTree);
	DialogAIController->UseBlackboard(DialogBlackBoard, BlackboardComponent);
	BlackboardComponent->SetValueAsObject(FName(TEXT("DialogWidget")), DialogWidgetAsset);
	if (ARifaNPC* ControllingNPC = Cast<ARifaNPC>(GetOwner()))
	{
		if (UMyGameInstance* GameInstance = Cast<UMyGameInstance>(UGameplayStatics::GetGameInstance(GetWorld())))
		{
			int32 DialogIndex = GameInstance->NPCDialogMap[ControllingNPC->ThisNPCType];
			BlackboardComponent->SetValueAsInt(FName(TEXT("DialogIndex")), DialogIndex);
		}
	}
	DialogWidgetAsset->Init();
}

void UDialogComponent::OnExit()
{
	DialogWidgetAsset->GetOwningPlayer()->SetInputMode(FInputModeGameOnly());
	DialogWidgetAsset->GetOwningPlayer()->bShowMouseCursor = false;
	DialogAIController->GetBrainComponent()->StopLogic(FString(TEXT("Dialog Exit")));
	DialogWidgetAsset->CloseWidget();
}

