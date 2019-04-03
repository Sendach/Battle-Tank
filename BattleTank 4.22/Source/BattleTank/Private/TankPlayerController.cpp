// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPlayerController.h"
#include "Tank.h"

ATankPlayerController::ATankPlayerController()
{
	CrossHairXLocation = 0.5f;
	CrossHairYLocation = 0.33333f;
}

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController does not possesing a tank"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController possesing: %s"), *ControlledTank->GetName());
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTowardsCrosshair();

}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (GetControlledTank())
	{
		FVector HitLocation; // OUT parameter
		if (GetSightRayHitLocation(HitLocation))
		{
			UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString());
		}
	}
}

// Gets world location of ray-trace through crosshair, true if it hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	// Size of current viewport
	int32 ViewPortSizeX, ViewPortSizeY;
	GetViewportSize(ViewPortSizeX, ViewPortSizeY);

	auto ScreenLocation = FVector2D(ViewPortSizeX * CrossHairXLocation,ViewPortSizeY * CrossHairYLocation);

	return true;
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}