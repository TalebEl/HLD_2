// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CustomPickUpBase.generated.h"

UCLASS()
class LAB2_API ACustomPickUpBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACustomPickUpBase();

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
		class UBoxComponent* BoxComponents;

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* StaticMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
