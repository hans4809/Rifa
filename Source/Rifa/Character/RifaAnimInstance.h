// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "RifaAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class RIFA_API URifaAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
public:
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Pawn)
	FVector Velocity;
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Pawn)
	float GroundSpeed;
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Pawn)
	bool IsFalling;
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Pawn)
	bool IsSwim;
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Pawn)
	bool IsFlying;
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Pawn)
	bool ShouldMove;
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Pawn)
	bool bIsDie;
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Pawn)
	class ARifaCharacter* RifaCharacter;
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Pawn)
	class UCharacterMovementComponent* RifaCharacterMovementComponent;
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Pawn)
	TObjectPtr<class ARifaGameMode> GameModeReference;
};
