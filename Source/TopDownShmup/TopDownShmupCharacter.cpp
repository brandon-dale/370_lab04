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

    // Set the initial Health
    Health = 100.0f;
    Alive = true;
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
                
                MyWeapon->MyPawn = this;
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

float ATopDownShmupCharacter::TakeDamage(float DamageTaken, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
    float ActualDamage = Super::TakeDamage(DamageTaken, DamageEvent, EventInstigator, DamageCauser);
    
    if (ActualDamage > 0.0f)
    {
        // TODO: Add a debug message on screen to know dwarf got hit
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(1, 1.0f, FColor::Green, FString::Printf(TEXT("Player Hit!")));
        }
        
        // Reduce health points
        Health -= ActualDamage;
        if (Health <= 0.0f)
        {
            // We're dead
            SetCanBeDamaged(false);  // Don't allow further damage
            // Process death
            Alive = false;
            // Disable Controls and stop firing
            AController* PlayerController = GetController();
            if (PlayerController)
            {
                PlayerController->SetIgnoreLookInput(true);
                PlayerController->SetIgnoreMoveInput(true);
                
                OnStopFire();
            }
            
            // Play the death animation
            DeathAnimDur = PlayAnimMontage(DeathAnim);
            GetWorldTimerManager().SetTimer(DeathAnimTimerMgr, this, &ATopDownShmupCharacter::DeactiveSkeletalMesh, DeathAnimDur, false, DeathAnimDur - 0.25);
        }
    }
    
    return ActualDamage;
}

// Returns true if the player is dead
bool ATopDownShmupCharacter::IsDead() const
{
    return !Alive;
}

void ATopDownShmupCharacter::DeactiveSkeletalMesh()
{
//    if (GEngine)
//    {
//        GEngine->AddOnScreenDebugMessage(3, 1.0f, FColor::Green, FString::Printf(TEXT("TODO!!! DEACTIVE THE PLAYER SKELETAL MESH")));
//    }
    // Add if statement
    GetMesh()->Deactivate();
}
