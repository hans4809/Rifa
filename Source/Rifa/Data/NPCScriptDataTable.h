// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "Character/RifaNPC.h"
#include "NPCScriptDataTable.generated.h"

UENUM(BlueprintType)
enum class EScriptType : uint8
{
	Speak UMETA(DisplayName = "Speak"),
	Reply UMETA(DisplayName = "Reply")
};

USTRUCT(Atomic, BlueprintType)
struct FNPCScriptTableKey
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Key")
	ENPCType NPCType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Key")
	int32 DialogIndex;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Key")
	EScriptType ScriptType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Key")
	int32 ScriptIndex;

	bool operator==(const FNPCScriptTableKey& Other) const
	{
		return NPCType == Other.NPCType && DialogIndex == Other.DialogIndex && ScriptType == Other.ScriptType && ScriptIndex == Other.ScriptIndex;
	}

	bool operator!=(const FNPCScriptTableKey& Other) const
	{
		return NPCType != Other.NPCType || DialogIndex != Other.DialogIndex || ScriptType != Other.ScriptType || ScriptIndex != Other.ScriptIndex;
	}

	bool operator < (const FNPCScriptTableKey& Other) const
	{
		if (NPCType != Other.NPCType)
		{
			return NPCType < Other.NPCType;
		}
		else if (DialogIndex != Other.DialogIndex)
		{
			return DialogIndex < Other.DialogIndex;
		}
		else if (ScriptType != Other.ScriptType)
		{
			return ScriptType < Other.ScriptType;
		}
		else
		{
			return ScriptIndex < Other.ScriptIndex;
		}
	}
	FNPCScriptTableKey()
	{
		this->NPCType = ENPCType::P0;
		this->DialogIndex = 0;
		this->ScriptType = EScriptType::Speak;
		this->ScriptIndex = 0;
	}

	FNPCScriptTableKey(ENPCType InNPCType, int32 InDialogIndex, EScriptType InScriptType, int32 InScriptIndex) : NPCType(InNPCType), DialogIndex(InDialogIndex), ScriptType(InScriptType), ScriptIndex(InScriptIndex) {}
};

USTRUCT(BlueprintType)
struct FNPCScriptTableRow : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Script")
	ENPCType NPCType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Script")
	int32 DialogIndex;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Script")
	EScriptType ScriptType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Script")
	int32 ScriptIndex;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Script")
	FText Script_ko;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Script")
	FText Script_en;
};

UCLASS()
class RIFA_API ANPCScriptDataTable : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANPCScriptDataTable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
