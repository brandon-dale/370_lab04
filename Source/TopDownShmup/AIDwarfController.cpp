// Fill out your copyright notice in the Description page of Project Settings.


#include "AIDwarfController.h"
#include "TopDownShmupCharacter.h"
#include "Kismet/GameplayStatics.h"

void AAIDwarfController::BeginPlay()
{
    Super::BeginPlay();
    
    SetCurrentState(EDwarfState::EStart);
    
    PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

    if (PlayerPawn)
    {
        MoveToActor(PlayerPawn);
    }

}

void AAIDwarfController::Tick(float DeltaTime)
{
    
    if (currentState == EDwarfState::EStart)
    {
        SetCurrentState(EDwarfState::EChasing);
    }
    
    else if (currentState == EDwarfState::EAttacking)
    {
        // Get position vectors for dwarf and player
        FVector DwarfLoc;
        if (AttachedPawn)
        {
            DwarfLoc = AttachedPawn->GetActorLocation();
        }
        FVector PlayerLoc;
        if (PlayerPawn)
        {
            PlayerLoc = PlayerPawn->GetActorLocation();
        }
        
        // Check distance to player
        if (FVector::Dist(DwarfLoc, PlayerLoc) > AttackRange)
        {
            SetCurrentState(EDwarfState::EChasing);
        }
        
        // Check if the player is dead
        ATopDownShmupCharacter* PlayerCharacter = Cast<ATopDownShmupCharacter>(PlayerPawn);
        if (PlayerCharacter && PlayerCharacter->IsDead())
        {
            ADwarfCharacter* Dwarf = Cast<ADwarfCharacter>(AttachedPawn);
            if (Dwarf)
            {
                Dwarf->StopAttack();
            }
        }
    }
    
}

void AAIDwarfController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);
    
    AttachedPawn = InPawn;
}

void AAIDwarfController::OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result)
{
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(3, 2.0f, FColor::Green, FString::Printf(TEXT("move completed")));
    }
    
    SetCurrentState(EDwarfState::EAttacking);
    
}


void AAIDwarfController::SetCurrentState(EDwarfState newState)
{
    if (newState == EDwarfState::EChasing && currentState != EDwarfState::EChasing)
    {
        // If start chasing, Move towards the player and stop attacking
        ADwarfCharacter* Dwarf = Cast<ADwarfCharacter>(AttachedPawn);
        if (Dwarf)
        {
            Dwarf->StopAttack();
        }
        
        if (PlayerPawn)
        {
            MoveToActor(PlayerPawn);
        }
    }
    else if (newState == EDwarfState::EAttacking)
    {
        ADwarfCharacter* Dwarf = Cast<ADwarfCharacter>(AttachedPawn);
        if (Dwarf)
        {
            Dwarf->StartAttack();
        }
    }
    
    currentState = newState;
}


EDwarfState AAIDwarfController::GetCurrentState() const
{
    return currentState;
}
