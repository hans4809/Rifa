// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyGameInstance.h"
#include "RifaCharacterParts.generated.h"

UCLASS()
class RIFA_API ARifaCharacterParts : public AActor
{
	GENERATED_BODY()


protected:
	ARifaCharacterParts();
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trigger", meta = (AllowPrivateAccess = "true"))
	class USphereComponent* Trigger;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	EHairPartsItem ThisHairPart;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* Mesh;
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
