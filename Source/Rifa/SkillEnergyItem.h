// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SkillEnergyItem.generated.h"

UENUM()
enum class EEnergyFeature : uint8
{
	Swim UMETA(DisplayName = "Swim"),
	Fly UMETA(DisplayName = "Fly")
};
UCLASS()
class RIFA_API ASkillEnergyItem : public AActor
{
	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USceneComponent* Root;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Mesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* Trigger;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UParticleSystemComponent* Particle;
public:	
	// Sets default values for this actor's properties
	ASkillEnergyItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Interaction, meta = (AllowPrivateAccess = "true"))
	bool IsInRange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UMyGameInstance> RifaGameInstance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data, meta = (AllowPrivateAccess = "true"))
	int ThisSkillItemIndex;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = Reference, meta = (AllowPrivateAccess = "true"))
	class ARifaCharacter* CharacterReference;
	UFUNCTION(BlueprintCallable)
	void OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION(BlueprintCallable)
	void EndCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = Widget, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> PickupTextClass;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = Reference, meta = (AllowPrivateAccess = "true"))
	class UPickupText* PickupTextReference;
	UFUNCTION(BlueprintCallable)
	void PickupEnergyEvent();
	UPROPERTY(EditAnyWhere)
	EEnergyFeature EnergyFeature;
};
