// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"
//#include

UCLASS()
class LAB1_API AProjectile : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    AProjectile();


    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
        class USphereComponent* SphereComponent;

    //UPROPERTY()


protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    UFUNCTION()
        void OnProjectileImpact(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

};
