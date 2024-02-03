// Fill out your copyright notice in the Description page of Project Settings.


#include "RifaAnimInstance.h"
#include "RifaCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <Kismet/GameplayStatics.h>
#include "RifaGameMode.h"


void URifaAnimInstance::NativeBeginPlay()
{
	RifaCharacter = Cast<ARifaCharacter>(GetOwningActor());
	RifaCharacterMovementComponent = RifaCharacter->GetCharacterMovement();
	GameModeReference = Cast<ARifaGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
}

void URifaAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (IsValid(RifaCharacter)){
		Velocity = RifaCharacter->GetVelocity();
		GroundSpeed = Velocity.Size();
		ShouldMove = (RifaCharacterMovementComponent->GetCurrentAcceleration() != FVector::ZeroVector) && (GroundSpeed > 3.0f);
		IsFalling = RifaCharacterMovementComponent->IsFalling();
		IsSwim = RifaCharacter->bIsSwimming;
		IsFlying = RifaCharacterMovementComponent->IsFlying();
		bIsDie = RifaCharacter->bIsDied;
	}
}
