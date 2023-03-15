// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"

// Sets default values
AWeapon::AWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    
    WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("RootComponent"));
    RootComponent = WeaponMesh;
    
    
    
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
    
	
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AWeapon::OnStartFire()
{
    FireAC = PlayWeaponSound(FireLoopSound);
    
    // QUESTIONABLE???
    ParticleSystemComp = UGameplayStatics::SpawnEmitterAttached(MuzzleFX, RootComponent, TEXT("MuzzleFlashSocket"));
//    if (ParticleSystemComp)
//    {
//        ParticleSystemComp->ActivateSystem();
//    }
    
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(1, 0.5f, FColor::Green, FString::Printf(TEXT("OnStartFire Called")));
    }
}


void AWeapon::OnStopFire()
{
    // Stop the sound and play the finished sound
    if (FireAC)
    {
        FireAC->Stop();
    }
    PlayWeaponSound(FireFinishSound);
    
    if (ParticleSystemComp)
    {
        ParticleSystemComp->DeactivateSystem();
    }
    
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(2, 0.5f, FColor::Green, FString::Printf(TEXT("OnStopFire Called")));
    }
}


UAudioComponent* AWeapon::PlayWeaponSound(USoundCue* Sound)
{
    UAudioComponent* AC = NULL;
    
    if (Sound)
    {
        AC = UGameplayStatics::SpawnSoundAttached(Sound, RootComponent);
    }
    
    return AC;
}
