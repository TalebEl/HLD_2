// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CustomUserWidget.generated.h"

/**
 *
 */
UCLASS()
class LAB2_API UCustomUserWidget : public UUserWidget
{
    GENERATED_BODY()


    virtual bool Initialize() override;
    virtual void NativeTick(const FGeometry& MyGeometry, float inDeltaTime) override;

    void UpdateNumGrenades();
};
