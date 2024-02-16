// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableActor.h"
#include "MyGameInstance.h"
#include "MaterailItem.generated.h"

/**
 * 
 */
UCLASS()
class RIFA_API AMaterailItem : public AInteractableActor
{
	GENERATED_BODY()
public:
	AMaterailItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	int32 CharacterMaterialArrIdx;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	ECharacterMaterialItem ECurrentMaterial;
	UFUNCTION(BlueprintCallable)
	void PickupCharacterMaterial();
};
