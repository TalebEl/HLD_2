// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Lab2Character.h"
#include "CustomProjectile.h"

// Sets default values
ACustomProjectile::ACustomProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Collsion   (SphereComponent)
	SphereComponent = CreateDefaultSubobject<USphereComponent>("Sphere Collision");
	//SphereComponent->SetCollisionProfileName("BlockAllDynamic");
	SphereComponent->SetupAttachment(StaticMesh);
	//SphereComponent->SetGenerateOverlapEvents(true);
	SphereComponent->OnComponentHit.AddDynamic(this, &ACustomProjectile::OnProjectileImpact);


	GrenadeCounter = 3.0f; // Grenade Timer 
	
	//The Static Mesh
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	StaticMesh->SetSimulatePhysics(false);
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	StaticMesh->SetWorldLocation(GetActorLocation());
	SetRootComponent(StaticMesh);

	


	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("SoundEmitter"));
	AudioComponent->bAutoActivate = false;
	AudioComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));

}


// Called when the game starts or when spawned
void ACustomProjectile::BeginPlay()
{
	Super::BeginPlay();

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
		UGameplayStatics::PlaySoundAtLocation(this->GetWorld(), ImpactSound, GetActorLocation());
		if (ProjectileFX)
		{
			UGameplayStatics::SpawnEmitterAtLocation(this, ProjectileFX, GetActorLocation());
		}
	    Destroy();
	}
}

// Called every frame
void ACustomProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//NOT WORKING
	//temp
	// Unique handle that can be used to distinguish timers that have identical delegates
	FTimerHandle TExplodeHandle;
	GetWorldTimerManager().SetTimer(TExplodeHandle, this, &ACustomProjectile::explode, GrenadeCounter, false);

	if (GrenadeCounter <= 0.0f)
	{
		Destroy();
	}

}

void ACustomProjectile::explode() // temp currently not working
{
	//NOT WORKING
	TArray<AActor*> OverlappingActors;
	SphereComponent->GetOverlappingActors(OverlappingActors, TSubclassOf<ALab2Character>());
}