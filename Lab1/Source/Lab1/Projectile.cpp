// Fill out your copyright notice in the Description page of Project Settings.

#include "GameFramework/ProjectileMovementComponent.h"
#include "Projectile.h"


#include "Components/AudioComponent.h" 

#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
//#include "AThirdPersonProjectile.h"

// Sets default values
AProjectile::AProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>("Sphere Collision");
	SphereComponent->SetCollisionProfileName("BlockAllDynamic");
	SphereComponent->SetGenerateOverlapEvents(true);
	SphereComponent->OnComponentHit.AddDynamic(this, &AProjectile::OnProjectileImpact);

	SetRootComponent(SphereComponent);


	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("SoundEmitter"));
	AudioComponent->bAutoActivate = false;
	AudioComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));

	/** ProjectileMovementComponent  */
	/*ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->UpdatedComponent = SphereComponent;
	ProjectileMovementComponent->InitialSpeed = InitialSpeed;
	ProjectileMovementComponent->MaxSpeed = MaximumSpeed;

	ProjectileMovementComponent->bRotationFollowsVelocity = false;
	ProjectileMovementComponent->bShouldBounce = true;*/


}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

}

void AProjectile::OnProjectileImpact(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{

	int x = 2;

	
		UGameplayStatics::SpawnEmitterAtLocation(this, ExplosionEffect, GetActorLocation(), FRotator::ZeroRotator, true, EPSCPoolMethod::AutoRelease);
		UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation(), FRotator::ZeroRotator);


	//Destroy();

}

void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//// Other Actor is the actor that triggered the event. Check that is not ourself. 
	//if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && !IsPendingKill())
	//{
	//	if (OtherActor != this->GetOwner())
	//	{

	//		//UGameplayStatics::PlaySoundAtLocation(this->GetWorld(), ImpactSound, GetActorLocation());
	//		//UGameplayStatics::SpawnEmitterAtLocation(this, ProjectileFX, GetActorLocation());
	//		//Destroy();


	//	}
	//}
	// Other Actor is the actor that triggered the event. Check that is not ourself. 
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && !IsPendingKill())
	{
		if (OtherActor != this->GetOwner())
		{
			//  if (OtherActor->ActorHasTag("AIGuard") || OtherActor->ActorHasTag("Player"))
			//  {
			 /* if (!AudioComponent->IsPlaying()) {
				  AudioComponent->SetSound(ImpactSound);
				  AudioComponent->Play();
			  }*/
			UGameplayStatics::PlaySoundAtLocation(this->GetWorld(), ImpactSound, GetActorLocation());
			if (ProjectileFX)
			{


				//Spawn ParticleSystem using GamePlayStatics
				UGameplayStatics::SpawnEmitterAtLocation(this, ProjectileFX, GetActorLocation());
				//OR Spawn Particle using UParticleSystemComponent
			   // PSC->SetTemplate(ProjectileFX);
				//ProjectileSprite->bHiddenInGame = true;
				//ProjectileSprite->SetVisibility(false);
			}
			Destroy();
			//    }

		}
	}
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

