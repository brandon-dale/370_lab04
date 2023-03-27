// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UObject/Object.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/AudioComponent.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"
#include "Weapon.generated.h"

UCLASS()
class TOPDOWNSHMUP_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();
    
    UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category=Weapon)
        USkeletalMeshComponent* WeaponMesh;
    
    virtual void OnStartFire();
    virtual void OnStopFire();
    
    UPROPERTY(EditDefaultsOnly, Category=Sound)
        USoundCue* FireLoopSound;
    UPROPERTY(EditDefaultsOnly, Category=Sound)
        USoundCue* FireFinishSound;
    
    UPROPERTY(EditDefaultsOnly, Category=FX)
        UParticleSystem* MuzzleFX;
    
    UPROPERTY(Transient)
        UParticleSystemComponent* ParticleSystemComp;
    
    APawn* MyPawn;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
    
    UPROPERTY(Transient)
        UAudioComponent* FireAC;
    
    UAudioComponent* PlayWeaponSound(USoundCue* Sound);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
