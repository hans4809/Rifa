// Copyright Epic Games, Inc. All Rights Reserved.

#include "RifaGameMode.h"
#include "RifaCharacter.h"
#include "UObject/ConstructorHelpers.h"

ARifaGameMode::ARifaGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
