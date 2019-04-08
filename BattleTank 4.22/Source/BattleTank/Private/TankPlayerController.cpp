// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Engine/World.h"

ATankPlayerController::ATankPlayerController()
{
	CrossHairXLocation = 0.5f;
	CrossHairYLocation = 0.33333f;
	AimLenght = 1000000; // 10 km

}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (ensure(AimingComponent))
	{
		FoundAimingComponent(AimingComponent);
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();

}

void ATankPlayerController::AimTowardsCrosshair()
{
	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (!ensure(AimingComponent)) { return; }

	FVector HitLocation; // OUT parameter

	if (GetSightRayHitLocation(HitLocation))
	{
		AimingComponent->AimAt(HitLocation);
	}
	
}

// Gets world location of ray-trace through crosshair, true if it hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	// Size of current viewport
	int32 ViewPortSizeX, ViewPortSizeY;
	GetViewportSize(ViewPortSizeX, ViewPortSizeY);
	auto ScreenLocation = FVector2D(ViewPortSizeX * CrossHairXLocation,ViewPortSizeY * CrossHairYLocation);

	///	//Calculates the direction of the crosshair in the world
	FVector AimDirection;
	if (GetAimDirection(ScreenLocation, AimDirection)) 
	{
		GetAimVectorHitLocation(HitLocation, AimDirection);
	}
	
	return true;
}

bool ATankPlayerController::GetAimDirection(FVector2D ScreenLocation, FVector& AimDirection) const
{
	FVector CameraWorldLocation;
	if (DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, AimDirection))
	{
		return true;
	}
	return false;
}

bool ATankPlayerController::GetAimVectorHitLocation(FVector& HitLocation, FVector AimDirection) const
{
	FHitResult HitResult;
	FVector StartOfRayTrace = PlayerCameraManager->GetCameraLocation();
	FVector EndOfRayTrace = StartOfRayTrace + (AimDirection * AimLenght);

	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartOfRayTrace, EndOfRayTrace, ECollisionChannel::ECC_Visibility))
	{
		HitLocation = HitResult.Location;
		return true;
	}
	HitLocation = FVector(0);
	return false;
}
