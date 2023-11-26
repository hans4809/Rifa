// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractionInterface.h"
#include "DialogComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RIFA_API UDialogComponent : public UActorComponent, public IInteractionInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDialogComponent();
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UPopUpWidget> DialogWidgetClass;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	class UDialogWidget* DialogWidgetAsset;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Dialog", meta = (AllowPrivateAccess = "true"))
	class ANPCAIController* DialogAIController;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Dialog", meta = (AllowPrivateAccess = "true"))
	class UBehaviorTree* DialogTree;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Dialog", meta = (AllowPrivateAccess = "true"))
	class UBlackboardData* DialogBlackBoard;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Dialog", meta = (AllowPrivateAccess = "true"))
	class UBlackboardComponent* BlackboardComponent;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
#pragma region InterfaceFunction
	// InteractionInterface 상속 때문에 override 선언
	UFUNCTION()
	virtual void UseAction() override;
	UFUNCTION()
	virtual void DropAction(AActor* DropToItem) override;
	UFUNCTION()
	virtual void OnInterAction(ARifaCharacter* InterActionCharacter) override;
#pragma endregion
	UFUNCTION()
	void OnExit();
};
