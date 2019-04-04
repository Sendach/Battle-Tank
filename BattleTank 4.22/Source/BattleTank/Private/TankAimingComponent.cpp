// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	// ...
}

void UTankAimingComponent::AimAt(FVector HitLocation, float BulletSpeed)
{
	if (Barrel)
	{
		FVector OutBulletVelocity = FVector(0);
		FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

		// Calculate the outLunchVelocity
		bool Check = UGameplayStatics::SuggestProjectileVelocity(this, OutBulletVelocity, StartLocation, HitLocation,
			BulletSpeed, ESuggestProjVelocityTraceOption::DoNotTrace);
		if (Check)
		{
			auto AimDirection = OutBulletVelocity.GetSafeNormal();
			MoveBarrelTowards(AimDirection);
		}
	}
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	//  Work-out difference between current barrel rotation and AimDirection
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	Barrel->Elevate(5.f);
}