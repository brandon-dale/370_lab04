// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIEnemyController.h"
#include "DwarfCharacter.h"
#include "AIDwarfController.generated.h"

UENUM(BlueprintType)
enum class EDwarfState: uint8
{
    EStart, EChasing, EAttacking, EDead, EUnknown
};


UCLASS()
class TOPDOWNSHMUP_API AAIDwarfController : public AAIEnemyController
{
	GENERATED_BODY()
    
public:
    
    virtual void BeginPlay() override;
    
    virtual void Tick(float DeltaTime) override;
	
    virtual void OnPossess(APawn* InPawn) override;
    
    virtual void OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type Result) override;
    
    APawn* AttachedPawn;
    
    UPROPERTY(EditAnywhere)
        EDwarfState currentState;
    
    void SetCurrentState(EDwarfState newState);
    
    EDwarfState GetCurrentState() const;
    
    UPROPERTY(EditAnywhere)
        float AttackRange = 150.0f;
    
    APawn* PlayerPawn;
    //ADwarfCharacter* Dwarf;
};

