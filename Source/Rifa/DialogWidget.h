// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PopUpWidget.h"
#include "DialogWidget.generated.h"

UENUM()
enum class EDialogState_C : uint8 // �Ǳ��̸�_���_�����
{
	Speak UMETA(DisplayName = "Speak"),
	Reply UMETA(DisplayName = "Reply")
};
/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDele_Dynam);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDele_Dynamic_Int, int32, ReplyIndex);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDele_Dynamic_Array, TArray<FString>, Replies);
UCLASS()
class RIFA_API UDialogWidget : public UPopUpWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	class USizeBox* ReplySizeBox;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	class USizeBox* SpeakSizeBox;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* SpeakText;
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, meta = (BindWidget))
	class UListView* ReplyList;
public:
	UFUNCTION(BlueprintCallable)
	void NativeConstruct();
	UFUNCTION(BlueprintCallable)
	virtual void Init() override;
	UFUNCTION(BlueprintCallable)
	virtual void CloseWidget() override;
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "Event")
	FDele_Dynam OnSpeakFinished;
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "Event")
	FDele_Dynamic_Int OnReplyFinished;
	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable, Category = "Event")
	FDele_Dynam OnExit;
	UFUNCTION(BlueprintCallable)
	void Speak_C(FText Text);
	UFUNCTION(BlueprintCallable)
	void Reply_C(TArray<FText> Replies);
	UFUNCTION(BlueprintCallable)
	void Exit_C();
	UFUNCTION(BlueprintCallable)
	void OnClicked_Event(class UDialogReplyObject* ClickedObject);
	UFUNCTION(BlueprintCallable)
	void SetDialogState_C(EDialogState_C DialogState);
	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	EDialogState_C CurrentDialogState;
};
