// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "TopDownShmupCharacter.h"
#include "TopDownShmup.h"

ATopDownShmupCharacter::ATopDownShmupCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

}


void ATopDownShmupCharacter::BeginPlay()
{
    Super::BeginPlay();
    
    if (WeaponClass)
    {
        UWorld* World = GetWorld();
        
        if (World)
        {
            FActorSpawnParameters SpawnParams;
            SpawnParams.Owner = this;
            SpawnParams.Instigator = GetInstigator();
            
            FRotator Rotation(0.0f, 0.0f, -90.0f);
            
            MyWeapon = World->SpawnActor<AWeapon>(WeaponClass, FVector::ZeroVector, Rotation, SpawnParams);
            
            if (MyWeapon)
            {
                MyWeapon->WeaponMesh->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::KeepRelative, true), TEXT("WeaponPoint"));
            }
            
        }
    }
}


void ATopDownShmupCharacter::OnStartFire()
{
    if (WeaponClass)
    {
        MyWeapon->OnStartFire();
    }
}

void ATopDownShmupCharacter::OnStopFire()
{
    if (WeaponClass)
    {
        MyWeapon->OnStopFire();
    }
}
