// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WaterFall.generated.h"

UCLASS()
class RIFA_API AWaterFall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWaterFall();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "WaterFall", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UStaticMeshComponent> Mesh;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "WaterFall", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UAudioComponent> Sound;	
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "WaterFall", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UNiagaraComponent> WaterFall;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "WaterFall", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UBoxComponent> BottomTrigger;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "WaterFall", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UBoxComponent> TopTrigger;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "WaterFall", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> BottomEndPoint;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "WaterFall", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USceneComponent> TopStartPoint;
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> WaterFallWidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UWaterFallWidget> WaterFallWidgetInstance;
private:
	UFUNCTION(BlueprintCallable)
	void OnCharacterBottomOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION(BlueprintCallable)
	void EndCharacterBottomOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION(BlueprintCallable)
	void OnCharacterTopOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION(BlueprintCallable)
	void EndCharacterTopOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
