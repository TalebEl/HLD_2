// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSBombActor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"//for the radial force
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"

// Sets default values
AFPSBombActor::AFPSBombActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BombBox = CreateDefaultSubobject<UBoxComponent>("BombBoxComponent");
	BombBox->SetCollisionProfileName("BlockAllDynamic");
	RootComponent = BombBox;
	BombBox->SetSimulatePhysics(true);


	BombMesh = CreateDefaultSubobject<UStaticMeshComponent>("BomvMeshComponent");
	BombMesh->SetupAttachment(RootComponent);
	BombMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	BombBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);


	 // Grenade Timer 
	//BombBox->SetNotifyRigidBodyCollision(true);
	//AddForce() : Function that will add force
	//#include "Components/PrimitiveComponent.h"
	//virtual void AddForce
	BombFuse = 2.0f;

	RadialImpulse = CreateDefaultSubobject<URadialForceComponent>(TEXT("RadialForceComponent"));
	RadialImpulse->bImpulseVelChange = true;
	RadialImpulse->ForceStrength = 1000.0f;
	RadialImpulse->ImpulseStrength = 1000.0f;
	RadialImpulse->Radius = 200.0f;
	RadialImpulse->SetupAttachment(RootComponent);
}


// Called when the game starts or when spawned
void AFPSBombActor::BeginPlay()
{
	Super::BeginPlay();
	BombMesh->AddRadialImpulse(GetActorLocation(), 500.0f, 2000.0f, ERadialImpulseFalloff::RIF_Constant, true);
}


void AFPSBombActor::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//UGameplayStatics::SpawnEmitterAtLocation(this, ExplosionEffect, GetActorLocation(), FRotator::ZeroRotator, true, EPSCPoolMethod::AutoRelease);
	//UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation(), FRotator::ZeroRotator);
	//Destroy();
	if (OtherActor != this->GetOwner())
	{
		FTimerHandle TExplodeHandle;
		GetWorldTimerManager().SetTimer(TExplodeHandle, this, &AFPSBombActor::Bombexplode, BombFuse, false);
	}
}

void AFPSBombActor::Hold(USkeletalMeshComponent* HoldingComponent)
{
	if (HoldingComponent)
	{
		BombBox->SetSimulatePhysics(false);
		BombBox->AttachToComponent(HoldingComponent, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), "Nothing");
	}
	
}

void AFPSBombActor::AddForce()
{

}

void AFPSBombActor::Bombexplode()
{
	RadialImpulse->FireImpulse();

	UGameplayStatics::PlaySoundAtLocation(this->GetWorld(), ImpactSound, GetActorLocation());
	if (ProjectileFX)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, ProjectileFX, GetActorLocation());
	}
	//StaticMesh->AddRadialImpulse(GetActorLocation(), 500.0f, 2000.0f, ERadialImpulseFalloff::RIF_Constant, true);


	Destroy();
}

void AFPSBombActor::BombOnRelease()
{
	BombMesh->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
	BombMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	//BombBox->SetSimulatePhysics(true);
	BombMesh->SetPhysicsLinearVelocity(FVector::ZeroVector);

}



// Called every frame
void AFPSBombActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

