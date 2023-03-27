// Fill out your copyright notice in the Description page of Project Settings.


#include "AssaultWeapon.h"
#include "DwarfCharacter.h"

AAssaultWeapon::AAssaultWeapon()
{
    FireRate = 0.05f;
    WeaponRange = 10000.0f;
    Damage = 2.0f;
}

void AAssaultWeapon::OnStartFire()
{
    Super::OnStartFire();
    
    GetWorldTimerManager().SetTimer(ShootingTimerMgr, this, &AAssaultWeapon::WeaponTrace, FireRate, true, 0.0f);
}


void AAssaultWeapon::OnStopFire()
{
    Super::OnStopFire();
    
    GetWorldTimerManager().ClearTimer(ShootingTimerMgr);
}

void AAssaultWeapon::WeaponTrace()
{
    static FName WeaponFireTag = FName(TEXT("WeaponTrace"));
    static FName MuzzleSocket = FName(TEXT("MuzzleFlashSocket"));
    
    // Start from the muzzle's position
    FVector StartPos = WeaponMesh->GetSocketLocation(MuzzleSocket);
    // Get forward vector of MyPawn
    FVector Forward = MyPawn->GetActorForwardVector();
    // Calculate end position
    FVector EndPos = StartPos + (Forward * WeaponRange);
    
    // Perform line trace to retrieve hit info
    FCollisionQueryParams TraceParams(WeaponFireTag, true, GetInstigator());
    
    // This fires the ray and checks against all objects w/ collision
    FHitResult Hit(ForceInit);
    GetWorld()->LineTraceSingleByObjectType(Hit, StartPos, EndPos, FCollisionObjectQueryParams::AllObjects, TraceParams);
    
    // Did this hit anything?
    if (Hit.bBlockingHit)
    {
        // Spawn Particle FX
        UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitEffect, Hit.ImpactPoint);
        
        // Apply Damage
        ADwarfCharacter* Dwarf = Cast<ADwarfCharacter>(Hit.GetActor());
        if (Dwarf)
        {
        Dwarf->TakeDamage(Damage, FDamageEvent(), GetInstigatorController(), this);
        }
    }
}
