// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Components/SphereComponent.h"
//#include "AThirdPersonProjectile.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>("Sphere Collision");
	SphereComponent->SetCollisionProfileName("BlockAllDynamic"); 
	//SphereComponent->SetGenerateOverlapEvents(true);
	SphereComponent->OnComponentHit.AddDynamic(this, &AProjectile::OnProjectileImpact);

	RootComponent = SphereComponent;



}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

void AProjectile::OnProjectileImpact(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{

	int x = 2;

	/*UGameplayStatics::spawnLocation(this, ExplosionEffect, spawnLocation, FRotator::ZeroRotator, true, EPSCPoolMethod::AutoRelease);
	UGameplayStatics::PlaySoundAtLocation(this, ExplosionSound, spawnLocation, FRotator::ZeroRotator);*/

	

}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

