// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "PhysicsEngine/RadialForceComponent.h"
//#include "Components/PrimitiveComponent.h" // For the impulse
#include "Lab2Character.h"
#include "CustomProjectile.h"


// Sets default values
ACustomProjectile::ACustomProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Collsion   (SphereComponent)
	SphereComponent = CreateDefaultSubobject<USphereComponent>("Sphere Collision");
	SphereComponent->SetCollisionProfileName("BlockAllDynamic");
	SphereComponent->SetupAttachment(StaticMesh);
	SphereComponent->SetGenerateOverlapEvents(true);
	SphereComponent->OnComponentHit.AddDynamic(this, &ACustomProjectile::OnHit);


	GrenadeFuse = 3.0f; // Grenade Timer 
	
	//The Static Mesh
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	StaticMesh->SetSimulatePhysics(false);
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	StaticMesh->OnComponentHit.AddDynamic(this, &ACustomProjectile::OnHit);
	StaticMesh->SetWorldLocation(GetActorLocation());
	SetRootComponent(StaticMesh);

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("SoundEmitter"));
	AudioComponent->bAutoActivate = false;
	AudioComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));

	//RadialImpulse From the Grenade
	RadialImpulse = CreateDefaultSubobject<URadialForceComponent>(TEXT("RadialForceComponent"));
	RadialImpulse->bImpulseVelChange = true;
	RadialImpulse->ForceStrength = 1000.0f;
	RadialImpulse->ImpulseStrength = 1000.0f;
	RadialImpulse->Radius = 200.0f;
	RadialImpulse->SetupAttachment(RootComponent);

}


// Called when the game starts or when spawned
void ACustomProjectile::BeginPlay()
{
	Super::BeginPlay();

	

	/*TArray<FHitResult> Hits;
	FVector MyLocation = GetActorLocation();*/

	StaticMesh->AddRadialImpulse(GetActorLocation(), 500.0f, 2000.0f, ERadialImpulseFalloff::RIF_Constant, true);

	//FCollisionShape* CollisionSphere = FCollisionShape::MakeSphere(500.0f);

	//bool isHit = GetWorld()->SweepMultiByChannel(Hits, MyLocation, MyLocation, FQuat::Identity, ECC_WorldStatic, MakeSphere);
}

void ACustomProjectile::OnProjectileImpact(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	//int x = 2;
	UGameplayStatics::SpawnEmitterAtLocation(this, ExplosionEffect, GetActorLocation(), FRotator::ZeroRotator, true, EPSCPoolMethod::AutoRelease);
	UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation(), FRotator::ZeroRotator);
	Destroy();
}

void ACustomProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor != this->GetOwner())
	{
		
			FTimerHandle TExplodeHandle;
			GetWorldTimerManager().SetTimer(TExplodeHandle, this, &ACustomProjectile::explode, GrenadeFuse, false);
	}
}

// Called every frame
void ACustomProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACustomProjectile::explode() // temp currently not working
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