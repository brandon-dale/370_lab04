// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/TargetPoint.h"
#include "SpawnManager.generated.h"

UCLASS()
class TOPDOWNSHMUP_API ASpawnManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnManager();
    
    UPROPERTY(EditAnywhere)
    TArray<ATargetPoint*>TargetPoints;
    
    UPROPERTY(EditAnywhere)
    TSubclassOf<ACharacter> CharacterToSpawn;
    
    UPROPERTY(EditAnywhere)
    float MinSpawnTime;
    
    UPROPERTY(EditAnywhere)
    float MaxSpawnTime;

    FTimerHandle SpawnTimerMgr;
    
    void SpawnCharacter();
    

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
    
private:
    void SpawnCharAt(FVector SpawnLoc);

};
