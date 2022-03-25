// Copyright Epic Games, Inc. All Rights Reserved.

#include "UE4_PlayerStartDemoGameMode.h"
#include "UE4_PlayerStartDemoCharacter.h"
#include "UObject/ConstructorHelpers.h"

AUE4_PlayerStartDemoGameMode::AUE4_PlayerStartDemoGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
