// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WaterFallActorByTriggerBox.generated.h"

UCLASS()
class RIFA_API AWaterFallActorByTriggerBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWaterFallActorByTriggerBox();
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "WaterFall", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> Root;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "WaterFall", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UBoxComponent> BottomTrigger;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "WaterFall", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UBoxComponent> TopTrigger;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "WaterFall", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UNiagaraComponent> WaterFall;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "WaterFall", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> TopStartPoint;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "WaterFall", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> BottomStartPoint;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "WaterFall", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> TopEndPoint;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "WaterFall", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> BottomEndPoint;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "WaterFall", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UStaticMeshComponent> Mesh;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "WaterFall", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UAudioComponent> Sound;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable)
	void OnCharacterBottomOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION(BlueprintCallable)
	void EndCharacterBottomOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION(BlueprintCallable)
	void OnCharacterTopOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION(BlueprintCallable)
	void EndCharacterTopOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
private:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = Widget, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> PickupTextClass;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = Reference, meta = (AllowPrivateAccess = "true"))
	class UPickupText* TopPickupTextReference;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = Reference, meta = (AllowPrivateAccess = "true"))
	class UPickupText* BottomPickupTextReference;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = Reference, meta = (AllowPrivateAccess = "true"))
	class ARifaCharacter* CharacterReference;
};
