// Fill out your copyright notice in the Description page of Project Settings.


#include "FlowWaterActor.h"
#include "Components/ArrowComponent.h"
#include "Character/RifaCharacter.h"

AFlowWaterActor::AFlowWaterActor()
{
	PrimaryActorTick.bCanEverTick = false;
	ArrowComponent = CreateEditorOnlyDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	if (ArrowComponent)
	{
		ArrowComponent->ArrowColor = FColor(150, 200, 255);
		ArrowComponent->bTreatAsASprite = true;
		ArrowComponent->SetupAttachment(Mesh);
		ArrowComponent->bIsScreenSizeScaled = true;
		ArrowComponent->SetSimulatePhysics(false);
	}
}

void AFlowWaterActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	/*if (bCharacterOverlapped) 
	{
		const FRotator CharacterRotation = CharacterReference->GetController()->GetControlRotation();
		const FRotator CharacterYawRotation(0, CharacterRotation.Yaw, 0);
		const FVector CharacterForwardDirection = FRotationMatrix(CharacterYawRotation).GetUnitAxis(EAxis::X);
	}*/
}

void AFlowWaterActor::BeginPlay()
{
	Super::BeginPlay();
}

void AFlowWaterActor::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnCharacterOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	bCharacterOverlapped = true;
	CharacterReference->WaterForcingVector = GetActorRightVector();
}

void AFlowWaterActor::EndCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	bCharacterOverlapped = false;
	Super::EndCharacterOverlap(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex);
	CharacterReference->WaterForcingVector.Set(0, 0, 0);
}
