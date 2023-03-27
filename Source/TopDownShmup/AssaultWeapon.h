// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "AssaultWeapon.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNSHMUP_API AAssaultWeapon : public AWeapon
{
	GENERATED_BODY()
        
    AAssaultWeapon();
        
    void OnStartFire();
    void OnStopFire();
    
public:
    
    UPROPERTY(EditAnywhere)
        float FireRate;
	
    UPROPERTY(EditAnywhere)
        float WeaponRange;
    
    UPROPERTY(EditDefaultsOnly)
        UParticleSystem* HitEffect;
    
    FTimerHandle ShootingTimerMgr;
    
    UPROPERTY(EditAnywhere)
        float Damage;
    
protected:
    void WeaponTrace();
};
