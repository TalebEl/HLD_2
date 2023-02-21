// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PhysicsEngine/RadialForceComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FPSBombActor.generated.h"

UCLASS()
class FPSGAME_API AFPSBombActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPSBombActor();

	UPROPERTY(EditDefaultsOnly, Category = "BombActor")
		class UStaticMeshComponent* BombMesh;

	UPROPERTY(EditDefaultsOnly, Category = "BombActor")
		class UBoxComponent* BombBox;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
		float BombFuse;

	UPROPERTY(EditAnywhere)
		URadialForceComponent* RadialImpulse;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
		UParticleSystem* ProjectileFX;

	UPROPERTY(EditAnywhere, Category = "Effects")
		class UParticleSystem* ExplosionEffect;

	//Maybe do not need???
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Custom", meta = (AllowPrivateAccess = "true"))
		class USoundBase* ImpactSound;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Custom", meta = (AllowPrivateAccess = "true"))
		class UAudioComponent* AudioComponent;

	UFUNCTION()
		void OnProjectileImpact(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	

public:	
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	void Hold(USkeletalMeshComponent* HoldingComponent);

	bool IsThrown;

	void Bombexplode();
	void OnRelease(FVector ForwardVector);//FVector ForwardVector
	void explode();

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	FTimerHandle TExplodeHandle;
};
