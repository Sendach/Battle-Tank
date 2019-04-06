// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"

#include "TankAimingComponent.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "Engine/World.h"
#include "TimerManager.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(TEXT("Aiming Component"));
	BulletSpeed = 4000.f;
	bCanFire = true;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ATank::AimAt(FVector HitLocation)
{
	TankAimingComponent->AimAt(HitLocation, BulletSpeed);
}

void ATank::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	TankAimingComponent->SetBarrelReference(BarrelToSet);
	Barrel = BarrelToSet;
}

void ATank::SetTurretReference(UTankTurret* TurretToSet)
{
	TankAimingComponent->SetTurretReference(TurretToSet);
}

void ATank::Fire()
{
	UE_LOG(LogTemp, Warning, TEXT("Shooting %d"), bCanFire);
	if (Barrel && bCanFire)
	{
		bCanFire = false;

		auto spawnedProjectile = GetWorld()->SpawnActor<AProjectile>(Projectile, Barrel->GetSocketLocation(FName("Projectile")), 
			Barrel->GetSocketRotation(FName("Projectile")));
		spawnedProjectile->LaunchProjectile(BulletSpeed);
		
		GetWorld()->GetTimerManager().SetTimer(FireTimerHandle, this, &ATank::ResetFire, RelaodTime, false);
	}
}

void ATank::ResetFire()
{
	bCanFire = true;
	GetWorld()->GetTimerManager().ClearTimer(FireTimerHandle);
}