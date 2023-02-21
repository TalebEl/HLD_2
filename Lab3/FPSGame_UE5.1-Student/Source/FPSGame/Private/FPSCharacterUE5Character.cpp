// Copyright Epic Games, Inc. All Rights Reserved.

#include "FPSCharacterUE5Character.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "BombDamageType.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "FPSBombActor.h"



//////////////////////////////////////////////////////////////////////////
// AFPSCharacterUE5Character

AFPSCharacterUE5Character::AFPSCharacterUE5Character()
{
	// Character doesnt have a rifle at start
	bHasRifle = false;

	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

	// Create a gun mesh component
	BombGripMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_BombGrip"));
	BombGripMeshComponent->CastShadow = false;
	BombGripMeshComponent->SetupAttachment(Mesh1P, "BombSocket");

	IsAbleToFire = true;

	RadialForceComponent = CreateDefaultSubobject<URadialForceComponent>(TEXT("RadialForceComponent"));
	RadialForceComponent->SetupAttachment(RootComponent);
}

void AFPSCharacterUE5Character::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

}

//////////////////////////////////////////////////////////////////////////// Input

void AFPSCharacterUE5Character::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		//Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AFPSCharacterUE5Character::Move);

		//Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AFPSCharacterUE5Character::Look);

		EnhancedInputComponent->BindAction(BombAction, ETriggerEvent::Triggered, this, &AFPSCharacterUE5Character::pickupBomb);

		//EnhancedInputComponent->BindAction(BombReleaseAction, ETriggerEvent::Completed, this, &AFPSCharacterUE5Character::BombRelease);
		EnhancedInputComponent->BindAction(BombAction, ETriggerEvent::Completed, this, &AFPSCharacterUE5Character::BombRelease);


		//EnhancedInputComponent->BindAction(BombReleaseAction, ETriggerEvent::Completed, this, &AFPSCharacterUE5Character::BombRelease);
	}
}

//Raycast a specific distance
void AFPSCharacterUE5Character::pickupBomb()
{
	//TAG or CAST A BOMB ACTOR : to only pickup the bomb

	AActor* PickedActor = RayCastActor();
	if (PickedActor)
	{
		AFPSBombActor* bomb = Cast<AFPSBombActor>(PickedActor);
		if (bomb)
		{
			Bomb = bomb;
			bomb->Hold(BombGripMeshComponent);
		}
		
	}


}

void AFPSCharacterUE5Character::BombRelease()
{
	if (Bomb)
	{
		//Bomb = GetWorld()->SpawnActor<AFPSBombActor>(BombActor);
		FVector Camloc;
		FRotator CamRot;

		Controller->GetPlayerViewPoint(Camloc, CamRot);

		Bomb->OnRelease(CamRot.Vector());

		
		//----stop velocity---
		// 
		//---add impulse---
	}

}

AActor* AFPSCharacterUE5Character::RayCastActor()
{
	if (Controller != nullptr)
	{
		FVector StarTrace;
		FVector Direction;
		FVector EndTrace;

		setupRay(StarTrace, Direction, EndTrace);

		UWorld* World = GetWorld();
		FHitResult Hit(ForceInit);
		FCollisionQueryParams TraceParams;
		TraceParams.AddIgnoredActor(this);
		TraceParams.bTraceComplex = true;
		World->LineTraceSingleByChannel(Hit, StarTrace, EndTrace, ECC_PhysicsBody, TraceParams);

		return Hit.GetActor();
	}
	return nullptr;
}

void AFPSCharacterUE5Character::setupRay(FVector& StartTrace, FVector& Direction, FVector& EndTrace)
{
	FVector Camloc;
	FRotator CamRot;

	Controller->GetPlayerViewPoint(Camloc, CamRot);

	StartTrace = Camloc;
	Direction = CamRot.Vector();
	//Distance of the pickup
	EndTrace = StartTrace + Direction * 300;




}


void AFPSCharacterUE5Character::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AFPSCharacterUE5Character::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AFPSCharacterUE5Character::SetHasRifle(bool bNewHasRifle)
{
	bHasRifle = bNewHasRifle;
}

bool AFPSCharacterUE5Character::GetHasRifle()
{
	return bHasRifle;
}
