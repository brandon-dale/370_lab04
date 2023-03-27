// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyCharacter.h"
#include "Animation/AnimMontage.h"
#include "TimerManager.h"
#include "DwarfCharacter.generated.h"

/**
 * 
 */
UCLASS()
class TOPDOWNSHMUP_API ADwarfCharacter : public AEnemyCharacter
{
	GENERATED_BODY()
    
public:
    
    ADwarfCharacter();
    
	UPROPERTY(EditDefaultsOnly)
        UAnimMontage* AttackAnim;
    
    void StartAttack();
    
    void StopAttack();
    
    UPROPERTY(EditAnywhere)
        float Health;
    
    UPROPERTY(EditAnywhere)
        float Damage;
    
    virtual float TakeDamage(float DamageTaken, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
    
    FTimerHandle AttackTimerMgr;
    
    float AttackAnimDur;
    
    void DamagePlayer();
    
    UPROPERTY(EditDefaultsOnly)
        UAnimMontage* DeathAnim;
    
    // Destroys the character and stops the timer
    void TriggerDestruction();
    
    FTimerHandle DeathAnimTimerMgr;
};
