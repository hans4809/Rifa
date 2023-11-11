// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InventoryStruct.h"
#include "InteractionInterface.h"
#include "RifaDataTable.h"
#include "Template_Pickup.generated.h"

UCLASS()
class RIFA_API ATemplate_Pickup : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USceneComponent* Root;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Mesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* Trigger;
public:	
	// Sets default values for this actor's properties
	ATemplate_Pickup();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom")
	UTexture2D* CustomImage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom")
	FString CustomPickupText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom")
	FString CustomActionText;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom")
	UStaticMesh* CustomStaticMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom")
	bool CustomBGM_On;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom")
	bool CustomIsHave;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Interaction, meta = (AllowPrivateAccess = "true"))
	bool IsInRange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Interaction, meta = (AllowPrivateAccess = "true"))
	int ItemIndex;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Item, meta = (AllowPrivateAccess = "true"))
	FItemStruct ItemInfo;
	UPROPERTY(EditAnyWhere)
	class UMyGameInstance* RifaGameInstance;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = Widget, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> PickupTextClass;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = Reference, meta = (AllowPrivateAccess = "true"))
	class UPickupText* PickupTextReference;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = Reference, meta = (AllowPrivateAccess = "true"))
	class ARifaCharacter* CharacterReference;
	UFUNCTION(BlueprintCallable)
	void OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION(BlueprintCallable)
	void EndCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION(BlueprintCallable)
	void PickupItemEvent();
};
