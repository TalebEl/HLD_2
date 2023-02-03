// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomGameModeBase.h"

ACustomGameModeBase::ACustomGameModeBase()
{
    const ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
    const ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game//Blueprints/BP_CustomPlayerController"));

    if (PlayerPawnBPClass.Class != NULL)
    {
        DefaultPawnClass = PlayerPawnBPClass.Class;
    }
    if (PlayerControllerBPClass.Class != NULL)
    {
        PlayerControllerClass = PlayerControllerBPClass.Class;
    }
}
