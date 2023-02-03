// Copyright Epic Games, Inc. All Rights Reserved.

#include "Lab2GameMode.h"
#include "Lab2Character.h"
#include "UObject/ConstructorHelpers.h"

ALab2GameMode::ALab2GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
