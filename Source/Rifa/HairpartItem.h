// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableActor.h"
#include "MyGameInstance.h"
#include "HairpartItem.generated.h"

/**
 * 
 */
UCLASS()
class RIFA_API AHairpartItem : public AInteractableActor
{
	GENERATED_BODY()
public:
	AHairpartItem();
private:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	int32 HairPartArrIdx;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	EHairPartsItem ECurrentHairPart;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> SKMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	ECharacterMaterialItem ECurrentMaterial;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION(BlueprintCallable)
	void PickupCharacterParts();
};
