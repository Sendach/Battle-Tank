// Fill out your copyright notice in the Description page of Project Settings.


#include "TankBarrel.h"
#include "Engine/World.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
	// Calculate the change in elevation - Clamping the result so it is between -1 amd 1
	RelativeSpeed = FMath::Clamp(RelativeSpeed, -1.f, 1.f);
	auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	// Get the new rotation/elevation of the barrel
	auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;
	// Clamp it so that the barrel can not move between our minimum and maximum elevation degrees
	auto Elevation = FMath::Clamp(RawNewElevation, MinElevationDegrees, MaxElevationDegrees);

	SetRelativeRotation(FRotator(Elevation, 0.f, 0.f));
}