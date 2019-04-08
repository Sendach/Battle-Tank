// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Engine/World.h"
#include "Projectile.h"
#include "TimerManager.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	// ...
}

void UTankAimingComponent::Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::Fire()
{
	if (!ensure(Barrel && Projectile)) { return; }
	if (bCanFire)
	{
		bCanFire = false;

		auto spawnedProjectile = GetWorld()->SpawnActor<AProjectile>(Projectile, Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile")));
		spawnedProjectile->LaunchProjectile(BulletSpeed);

		GetWorld()->GetTimerManager().SetTimer(FireTimerHandle, this, &UTankAimingComponent::ResetFire, RelaodTime, false);
	}
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (ensure(Barrel))
	{
		UE_LOG(LogTemp, Warning, TEXT("YAYEE"));

		FVector OutBulletVelocity;
		FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
		
		// Calculate the outLunchVelocity
		bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(this, OutBulletVelocity, StartLocation, HitLocation,
			BulletSpeed, false, 0.f, 0.f, ESuggestProjVelocityTraceOption::DoNotTrace);
		if (bHaveAimSolution)
		{
			auto AimDirection = OutBulletVelocity.GetSafeNormal();
			MoveBarrelTowards(AimDirection);
			RotateTurret(AimDirection);
		}
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (ensure(Barrel))
	{
		//  Work-out difference between current barrel rotation and AimDirection
		auto BarrelRotator = Barrel->GetForwardVector().Rotation();
		auto AimAsRotator = AimDirection.Rotation();
		auto DeltaRotator = AimAsRotator - BarrelRotator;

		Barrel->Elevate(DeltaRotator.Pitch);
	}
}

void UTankAimingComponent::RotateTurret(FVector AimDirection)
{
	if (ensure(Turret))
	{
		auto TurretRotator = Turret->GetForwardVector().Rotation();
		auto AimAsRotator = AimDirection.Rotation();
		auto DeltaRotator = AimAsRotator - TurretRotator;

		Turret->Azimuth(DeltaRotator.Yaw);
	}
}

void UTankAimingComponent::ResetFire()
{
	bCanFire = true;
	GetWorld()->GetTimerManager().ClearTimer(FireTimerHandle);
}
