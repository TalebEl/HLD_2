// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomUserWidget.h"
#include "Components/TextBlock.h"
#include "Lab2Character.h"
#include "Kismet/GameplayStatics.h"

bool UCustomUserWidget::Initialize()
{
    bool bResult = Super::Initialize();
    UTextBlock* Widget = Cast<UTextBlock>(GetWidgetFromName("TextBlock_69"));

    if (Widget)
    {
        Widget->SetText(FText::FromString("TEMP "));
    }

    return bResult;
}

void UCustomUserWidget::NativeTick(const FGeometry& MyGeometry, float inDeltaTime)
{
    Super::NativeTick(MyGeometry, inDeltaTime);
    UpdateNumGrenades();
}

void UCustomUserWidget::UpdateNumGrenades()
{
    AController* pController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    APawn* playerPawn = pController->GetPawn();
    ALab2Character* Player = Cast<ALab2Character>(playerPawn);

    UTextBlock* Widget = Cast<UTextBlock>(GetWidgetFromName("TextBlock_69"));

    if (Widget)
    {
        //That handle the UI ---- Grenade:5(by decrementing --)
        Widget->SetText(FText::FromString("Grenades: " +FString::FromInt(Player->NumGrenades)));
    }
}
