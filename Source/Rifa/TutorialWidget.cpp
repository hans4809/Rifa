// Fill out your copyright notice in the Description page of Project Settings.


#include "TutorialWidget.h"
#include "Components/Image.h"
#include "Engine/Texture2D.h"

void UTutorialWidget::NativeConstruct()
{
	Super::NativeConstruct();
	TutorialImage = Cast<UImage>(GetWidgetFromName(TEXT("TutorialImage")));

	const UEnum* TutorialTypeName = FindObject<UEnum>(nullptr, TEXT("/Script/Rifa.ETutorialType"));
	if (TutorialTypeName)
	{
		FString EnumMetaData = TutorialTypeName->GetDisplayNameTextByValue((int64)ThisTutorialType).ToString();
		FString TutorialTexturePath = FString::Printf(TEXT("/Script/Engine.Texture2D'/Game/UIPNG/Tutorial-%s.Tutorial-%s'"), *EnumMetaData, *EnumMetaData);
		UTexture2D* TutorialTexture = LoadObject<UTexture2D>(NULL, *TutorialTexturePath, NULL, LOAD_None, NULL);
		if (IsValid(TutorialTexture))
		{
			TutorialImage->SetBrushFromTexture(TutorialTexture);
		}
	}
}

//FString GetBodyEnumAsString(ETutorialType value)
//{
//	const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("ETutorialType"), true);
//	if (!EnumPtr) return FString("Invalid");
//
//	return EnumPtr->GetNameStringByIndex((int32)value);
//}