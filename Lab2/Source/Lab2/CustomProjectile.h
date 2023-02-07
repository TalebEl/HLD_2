// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PhysicsEngine/RadialForceComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CustomProjectile.generated.h"


UCLASS()
class LAB2_API ACustomProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACustomProjectile();

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
        class USphereComponent* SphereComponent;

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
        float GrenadeFuse;

    UPROPERTY(VisibleAnywhere)
        UStaticMeshComponent* StaticMesh;

    UPROPERTY(EditAnywhere)
        URadialForceComponent* RadialImpulse;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AAA", meta = (AllowPrivateAccess = "true"))
        class UProjectileMovementComponent* ProjectileMovementComponent;

    


protected:
    //delete later
    //virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
    
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    /*UPROPERTY(EditDefaultsOnly, Category = "Effects")
        UParticleSystem* ProjectileFX;*/

    UPROPERTY(EditDefaultsOnly, Category = "Effects")
        UParticleSystem* ProjectileFX;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
        int MaximumSpeed = 2000;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
        int InitialSpeed = 1500;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Custom", meta = (AllowPrivateAccess = "true"))
        class USoundBase* ImpactSound;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Custom", meta = (AllowPrivateAccess = "true"))
        class UAudioComponent* AudioComponent;

    UPROPERTY(EditAnywhere, Category = "Effects")
        class UParticleSystem* ExplosionEffect;

    UPROPERTY(EditAnywhere, Category = "Effects")
        class USoundBase* ExplosionSound;

    UFUNCTION()
        void OnProjectileImpact(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);


    UFUNCTION()
        void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);


public:

    // Called every frame
    virtual void Tick(float DeltaTime) override;

    void explode();
};
