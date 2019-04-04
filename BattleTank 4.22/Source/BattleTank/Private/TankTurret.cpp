// Fill out your copyright notice in the Description page of Project Settings.


#include "TankTurret.h"
#include "Engine/World.h"

void UTankTurret::Azimuth(float RelativeSpeed)
{
	// Calculate the change in elevation - Clamping the result so it is between -1 amd 1
	RelativeSpeed = FMath::Clamp(RelativeSpeed, -1.f, 1.f);
	auto AzimuthChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	// Get the new rotation/elevation of the barrel
	auto Azimuth = RelativeRotation.Yaw + AzimuthChange;
	SetRelativeRotation(FRotator(0.f, Azimuth, 0.f));
}