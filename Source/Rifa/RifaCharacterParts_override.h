// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RifaCharacterParts.h"
#include "RifaCharacterParts_override.generated.h"

/**
 * 
 */
UCLASS()
class RIFA_API ARifaCharacterParts_override : public ARifaCharacterParts
{
	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* Trigger;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
public:
	// Sets default values for this actor's properties
	ARifaCharacterParts_override();
	UFUNCTION(BlueprintCallable)
	void PickupCharacterParts();
	UFUNCTION(BlueprintCallable)
	void OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION(BlueprintCallable)
	void EndCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = Widget, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> PickupTextClass;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = Reference, meta = (AllowPrivateAccess = "true"))
	class UPickupText* PickupTextReference;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Interaction, meta = (AllowPrivateAccess = "true"))
	bool IsInRange;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = Reference, meta = (AllowPrivateAccess = "true"))
	class ARifaCharacter* CharacterReference;
};
