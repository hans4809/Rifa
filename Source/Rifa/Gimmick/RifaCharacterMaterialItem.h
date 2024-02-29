// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Data/MyGameInstance.h"
#include "RifaCharacterMaterialItem.generated.h"

UCLASS()
class RIFA_API ARifaCharacterMaterialItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARifaCharacterMaterialItem();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trigger", meta = (AllowPrivateAccess = "true"))
	class USphereComponent* Trigger;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	int32 CharacterMaterialArrIdx;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	UStaticMeshComponent* Mesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	ECharacterMaterialItem ECurrentMaterial;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reference")
	TObjectPtr<UMyGameInstance> RifaGameInstance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reference")
	TObjectPtr<class ARifaGameMode> RifaGameMode;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reference")
	TObjectPtr<class ABaseLevelScriptActor> CurrentLevelScriptActorReference;
	
	UFUNCTION(BlueprintCallable)
	void PickupCharacterMaterial();
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
