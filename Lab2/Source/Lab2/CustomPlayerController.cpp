// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomPlayerController.h"
#include "CustomUserWidget.h"

void ACustomPlayerController::BeginPlay()
{
    Super::BeginPlay();
    if (GameInfoBP != nullptr)
    {
        GameInfoWidget = CreateWidget<UCustomUserWidget>(this, GameInfoBP);
        GameInfoWidget->AddToViewport();
    }
}
