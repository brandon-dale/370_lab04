// Fill out your copyright notice in the Description page of Project Settings.


#include "DwarfCharacter.h"
#include "TopDownShmupCharacter.h"
#include "AIDwarfController.h"

ADwarfCharacter::ADwarfCharacter()
{
    // Set the AI Controller Class
    AIControllerClass = AAIDwarfController::StaticClass();
    
    // Set the initial health
    Health = 20.0f;
    Damage = 10.0f;
}

void ADwarfCharacter::StartAttack()
{
    // Start Animation and timer
    AttackAnimDur = PlayAnimMontage(AttackAnim);
    
    GetWorldTimerManager().SetTimer(AttackTimerMgr, this, &ADwarfCharacter::DamagePlayer, AttackAnimDur, true, 0.0f);
}

void ADwarfCharacter::StopAttack()
{
    StopAnimMontage(AttackAnim);
    
    GetWorldTimerManager().ClearTimer(AttackTimerMgr);
}

float ADwarfCharacter::TakeDamage(float DamageTaken, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
    float ActualDamage = Super::TakeDamage(DamageTaken, DamageEvent, EventInstigator, DamageCauser);
    
    if (ActualDamage > 0.0f)
    {
        // TODO: Add a debug message on screen to know dwarf got hit
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(1, 1.0f, FColor::Green, FString::Printf(TEXT("Dwarf Hit!")));
        }
        
        // Reduce health points
        Health -= ActualDamage;
        if (Health <= 0.0f)
        {
            // We're dead
            SetCanBeDamaged(false);  // Don't allow further damage
            //TODO: Process death
            // Stop attack animation
            StopAttack();
            // UnPossess the AI controller
            AController* AIController = GetController();
            if (AIController)
            {
                AIController->UnPossess();
            }
            // Play the death animation and trigger the timer to destroy the character
            float DeathAnimDur = PlayAnimMontage(DeathAnim);
            GetWorldTimerManager().SetTimer(DeathAnimTimerMgr, this, &ADwarfCharacter::TriggerDestruction, DeathAnimDur, false, DeathAnimDur);
        }
    }
    
    return ActualDamage;
}

void ADwarfCharacter::DamagePlayer()
{
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if (PlayerPawn)
    {
        PlayerPawn->TakeDamage(Damage, FDamageEvent(), GetInstigatorController(), this);
    }
}

// Destroys the character and clears the death animation timer
void ADwarfCharacter::TriggerDestruction()
{
    GetWorldTimerManager().ClearTimer(DeathAnimTimerMgr);
    Destroy();
    
}
