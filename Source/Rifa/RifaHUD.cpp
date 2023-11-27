// Fill out your copyright notice in the Description page of Project Settings.


#include "RifaHUD.h"

void ARifaHUD::ReceiveDrawHUD(int32 SizeX, int32 SizeY)
{
	Super::ReceiveDrawHUD(SizeY, SizeY);
	if (ShowCrossHair) 
	{
		//DrawTexture()
		UE_LOG(LogTemp, Log, TEXT("ReceiveDrawHUD"));
	}
}
