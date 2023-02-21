// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSBombActor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PhysicsEngine/RadialForceComponent.h"//for the radial force
#include "Components/AudioComponent.h"
#include "Runtime/Engine/Classes/Particles/ParticleSystemComponent.h"
#include "Runtime/Engine/Public/TimerManager.h"

// Sets default values
AFPSBombActor::AFPSBombActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BombBox = CreateDefaultSubobject<UBoxComponent>("BombBoxComponent");
	BombBox->SetCollisionProfileName("BlockAllDynamic");
	RootComponent = BombBox;
	BombBox->SetSimulatePhysics(true);
	BombBox->SetGenerateOverlapEvents(true);//temp


	BombMesh = CreateDefaultSubobject<UStaticMeshComponent>("BomvMeshComponent");
	BombMesh->SetupAttachment(RootComponent);
	BombMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	BombBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	 
   BombBox->SetNotifyRigidBodyCollision(true);
   BombBox->OnComponentHit.AddDynamic(this, &AFPSBombActor::OnHit);//temp
   // Grenade Timer
	BombFuse = 2.0f;//must be 2sec

	RadialImpulse = CreateDefaultSubobject<URadialForceComponent>(TEXT("RadialForceComponent"));
	RadialImpulse->bImpulseVelChange = true;
	RadialImpulse->bAutoActivate = false;//temp
	RadialImpulse->bIgnoreOwningActor = true;//temp
	RadialImpulse->ForceStrength = 1000.0f;
	RadialImpulse->ImpulseStrength = 1000.0f;
	RadialImpulse->Radius = 200.0f;
	RadialImpulse->SetupAttachment(RootComponent);//RootComponent
	
	IsThrown = false;

	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("SoundEmitter"));
	AudioComponent->bAutoActivate = false;
	AudioComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
}


// Called when the game starts or when spawned
void AFPSBombActor::BeginPlay()
{
	Super::BeginPlay();
	//BombMesh->AddRadialImpulse(GetActorLocation(), 500.0f, 2000.0f, ERadialImpulseFalloff::RIF_Constant, true);
}


void AFPSBombActor::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	//UGameplayStatics::SpawnEmitterAtLocation(this, ExplosionEffect, GetActorLocation(), FRotator::ZeroRotator, true, EPSCPoolMethod::AutoRelease);
	//UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation(), FRotator::ZeroRotator);
	//Destroy();
	if (IsThrown == true)
	{
		GetWorld()->GetTimerManager().SetTimer(TExplodeHandle, this, &AFPSBombActor::Bombexplode, BombFuse); //temp
		/*if (OtherActor != this->GetOwner())
		{
			GetWorldTimerManager().SetTimer(TExplodeHandle, this, &AFPSBombActor::Bombexplode, BombFuse, false);

		}*/
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

void AFPSBombActor::OnRelease(FVector ForwardVector)
{
	//ForwardVector *= 2500.0f;//Impulse
	//IsThrown = true;

	//BombMesh->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);//datach the bomb from the character
	BombBox->SetSimulatePhysics(true); // already set to true in constructor
	//BombMesh->SetPhysicsLinearVelocity(FVector::ZeroVector);
	BombBox->AddForce(ForwardVector * 100000, NAME_None, true);
	//BombBox->AddImpulse(ForwardVector);
	IsThrown = true;
	//Destroy();
}



// Called every frame
void AFPSBombActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFPSBombActor::explode()
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

void AFPSBombActor::OnProjectileImpact(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	UGameplayStatics::SpawnEmitterAtLocation(this, ExplosionEffect, GetActorLocation(), FRotator::ZeroRotator, true, EPSCPoolMethod::AutoRelease);
	UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation(), FRotator::ZeroRotator);
	Destroy();
}