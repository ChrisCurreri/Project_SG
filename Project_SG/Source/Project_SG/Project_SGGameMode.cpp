// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "Project_SGGameMode.h"
#include "Project_SGCharacter.h"
#include "UObject/ConstructorHelpers.h"

AProject_SGGameMode::AProject_SGGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Characters/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
