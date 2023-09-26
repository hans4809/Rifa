// Fill out your copyright notice in the Description page of Project Settings.


#include "RifaAnimInstance.h"
#include "RifaCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"


void URifaAnimInstance::NativeBeginPlay()
{
	RifaCharacter = Cast<ARifaCharacter>(GetOwningActor());
	RifaCharacterMovementComponent = RifaCharacter->GetCharacterMovement();
}

void URifaAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	auto Pawn = TryGetPawnOwner();
	if (IsValid(RifaCharacter)){
		Speed = RifaCharacter->GetVelocity().Size();
		ShouldMove = (RifaCharacterMovementComponent->GetCurrentAcceleration() != FVector::ZeroVector) && (Speed > 3.0f);
		IsFalling = RifaCharacterMovementComponent->IsFalling();
		IsSwim = RifaCharacter->IsSwimming;
		IsFlying = RifaCharacterMovementComponent->IsFlying();
		//IsFlying = Cast<ARifaCharacter>(Character)->IsFlying;

	}
}
