// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class AProjectile;

UENUM()
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Locked
};

class UTankBarrel;
class UTankTurret;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet);

	UFUNCTION(BlueprintCallable, Category = "Fire")
	void Fire();

private:
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;

	void MoveBarrelTowards(FVector AimDirection);
	void RotateTurret(FVector AimDirection);

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float BulletSpeed = 300.0f;

	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::Aiming;

	//Resets ability to fire
	void ResetFire();

	UPROPERTY(EditAnywhere, Category = "Setup")
	TSubclassOf<AProjectile> Projectile;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float RelaodTime = 3.0f;

	bool bCanFire = true;
	FTimerHandle FireTimerHandle;
};
