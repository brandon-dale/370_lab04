// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnManager.h"
#include "Components/SkeletalMeshComponent.h"
#include "DwarfCharacter.h"

// Sets default values
ASpawnManager::ASpawnManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ASpawnManager::BeginPlay()
{
	Super::BeginPlay();
	
    // Start Spawn Timer
    GetWorldTimerManager().SetTimer(SpawnTimerMgr, this, &ASpawnManager::SpawnCharacter, MinSpawnTime, false, 0);
    
}

// Called every frame
void ASpawnManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


// Spawns a character from a random points and RESTARTS the regular spawn timer
void ASpawnManager::SpawnCharacter()
{
//    if (GEngine)
//    {
//        GEngine->AddOnScreenDebugMessage(-7, 1.0f, FColor::Green, FString::Printf(TEXT("Character Spawned")));
//    }
    
    // Stop the spawn timer
    GetWorldTimerManager().ClearTimer(SpawnTimerMgr);
    
    // Pick a random spawn point
    int randIndex = FMath::RandRange(0, TargetPoints.Num() - 1);
    ATargetPoint* SpawnPoint = TargetPoints[randIndex];
        
    // Spawn the character and enable default controller
    if (SpawnPoint)
    {
        FVector SpawnLoc = SpawnPoint->GetActorLocation();
        SpawnCharAt(SpawnLoc);
    }
    
    // Start the spawn timer
    float SpawnTime = FMath::FRandRange(MinSpawnTime, MaxSpawnTime);
    GetWorldTimerManager().SetTimer(SpawnTimerMgr, this, &ASpawnManager::SpawnCharacter, SpawnTime, false, SpawnTime);
}

void ASpawnManager::SpawnCharAt(FVector SpawnLoc)
{
    if (CharacterToSpawn)
    {
        UWorld* World = GetWorld();
        
        if (World)
        {
            FActorSpawnParameters SpawnParams;
            SpawnParams.Owner = this;
            SpawnParams.Instigator = GetInstigator();
                
            ACharacter* SpawnedChar = World->SpawnActor<ACharacter>(CharacterToSpawn, SpawnLoc, FRotator::ZeroRotator, SpawnParams);
        
            if (SpawnedChar)
            {
                SpawnedChar->SpawnDefaultController();
        
            }
        }
    }
}
    
