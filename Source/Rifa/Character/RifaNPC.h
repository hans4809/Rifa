// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "RifaNPC.generated.h"

UENUM()
enum class ENPCType : uint8
{
	A0 UMETA(DisplayName = "A0"),
	A1 UMETA(DisplayName = "A1"),
	A2 UMETA(DisplayName = "A2"),
	A3 UMETA(DisplayName = "A3"),
	P0 UMETA(DisplayName = "P0"),
	P2 UMETA(DisplayName = "P2"),
	R0 UMETA(DisplayName = "R0"),
	R1 UMETA(DisplayName = "R1"),
	R2 UMETA(DisplayName = "R2"),
	R3 UMETA(DisplayName = "R3"),
	S0 UMETA(DisplayName = "S0"),
	S1 UMETA(DisplayName = "S1"),
	S2 UMETA(DisplayName = "S2"),
	S3 UMETA(DisplayName = "S3"),
	T0 UMETA(DisplayName = "T0"),
	T3 UMETA(DisplayName = "T3"),
	MaxCount UMETA(Hidden)
};
UCLASS()
class RIFA_API ARifaNPC : public ACharacter
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Collision, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* Trigger;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Dialog", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UDialogComponent> DialogComponent;
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Widget", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UWidgetComponent> WidgetComponent;
public:
	// Sets default values for this character's properties
	ARifaNPC();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	UFUNCTION(BlueprintCallable)
	void Dialog();
	UFUNCTION()
	FORCEINLINE class UDialogComponent* GetDialogCommponent() const { return DialogComponent; }
private:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = Widget, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> PickupTextClass;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = Reference, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UPickupText> PickupTextReference;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = Reference, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class ARifaCharacter> CharacterReference;
	UFUNCTION(BlueprintCallable)
	void OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION(BlueprintCallable)
	void EndCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Interaction, meta = (AllowPrivateAccess = "true"))
	bool IsInRange;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Interaction)
	ENPCType ThisNPCType;

};
