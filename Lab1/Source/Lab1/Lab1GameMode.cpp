// Copyright Epic Games, Inc. All Rights Reserved.

#include "Lab1GameMode.h"
#include "Lab1Character.h"
#include "UObject/ConstructorHelpers.h"

ALab1GameMode::ALab1GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
