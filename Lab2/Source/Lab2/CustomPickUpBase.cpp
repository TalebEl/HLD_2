// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Lab2Character.h"
#include "CustomPickUpBase.h"

// Sets default values
ACustomPickUpBase::ACustomPickUpBase()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    //The Static Mesh
    StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    StaticMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    //StaticMesh->OnComponentBeginOverlap.AddDynamic(this, &ACustomPickUpBase::OnBoxBeginOverlap);
    //StaticMesh->SetWorldLocation(GetActorLocation());//
    SetRootComponent(StaticMesh);

    //Collsion   (Box Components)
    BoxComponents = CreateDefaultSubobject<UBoxComponent>("Box Collision");
    BoxComponents->SetCollisionProfileName("OverlapAllDynamic");
    BoxComponents->SetupAttachment(StaticMesh);
    //BoxComponents->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    //SetRootComponent(BoxComponents);
    BoxComponents->SetGenerateOverlapEvents(true);
    BoxComponents->OnComponentBeginOverlap.AddDynamic(this, &ACustomPickUpBase::OnBoxBeginOverlap);

}

// Called when the game starts or when spawned
void ACustomPickUpBase::BeginPlay()
{
    Super::BeginPlay();

}

void ACustomPickUpBase::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    ALab2Character* Player = Cast<ALab2Character>(OtherActor);

    if (Player != nullptr)
    {
        Player->NumGrenades = 5;
        Player->TextComponent->SetText(FText::FromString(FString::FromInt(Player->NumGrenades)));
    }

}


// Called every frame
void ACustomPickUpBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

