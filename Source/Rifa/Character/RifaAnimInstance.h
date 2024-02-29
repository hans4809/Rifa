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
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	FVector Velocity;
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	float GroundSpeed;
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool IsFalling;
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool IsSwim;
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool IsFlying;
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool ShouldMove;
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	bool bIsDie;
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	class ARifaCharacter* RifaCharacter;
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	class UCharacterMovementComponent* RifaCharacterMovementComponent;
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = Pawn, Meta = (AllowPrivateAccess = true))
	TObjectPtr<class ARifaGameMode> GameModeReference;
};
