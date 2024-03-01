// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InteractableActor.h"
#include "Widget/InventoryStruct.h"
#include "SoundItem.generated.h"

/**
 * 
 */
UCLASS()
class RIFA_API ASoundItem : public AInteractableActor
{
	GENERATED_BODY()
public:
	ASoundItem();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom")
	TObjectPtr<UTexture2D> CustomImage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom")
	FString CustomItemName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom")
	FString CustomActionText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom")
	TObjectPtr<UStaticMesh> CustomStaticMesh;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "LevelSequence")
	TObjectPtr<class ALevelSequenceActor> LevelSequencActor;
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UNiagaraComponent> Particle;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = Data, meta = (AllowPrivateAccess = "true"))
	int32 ThisSoundItemIndex;
	UFUNCTION(BlueprintCallable)
	void PickupSoundItemEvent();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION()
	void OnEndLevelSequence();
};
