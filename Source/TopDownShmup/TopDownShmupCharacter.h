// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include "Weapon.h"
#include "Templates/SubclassOf.h"
#include "TopDownShmupCharacter.generated.h"

UCLASS(Blueprintable)
class ATopDownShmupCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;
    
    AWeapon* MyWeapon;


protected:
    virtual void BeginPlay() override;
    
public:
	ATopDownShmupCharacter();

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
    
    UPROPERTY(EditAnywhere, Category=Weapon)
    TSubclassOf<AWeapon> WeaponClass;
    
    void OnStartFire();
    void OnStopFire();

    UPROPERTY(EditAnywhere)
    float Health;
    
    bool Alive;
    
    virtual float TakeDamage(float DamageTaken, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

    bool IsDead() const;
    
    UPROPERTY(EditDefaultsOnly)
        UAnimMontage* DeathAnim;
    
    float DeathAnimDur;
    
    FTimerHandle DeathAnimTimerMgr;
    
    void DeactiveSkeletalMesh();
};

