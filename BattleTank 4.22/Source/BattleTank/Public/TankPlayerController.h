// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class UTankAimingComponent;

UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
	void FoundAimingComponent(UTankAimingComponent* AimCompRed);

public:
	ATankPlayerController();
	virtual void Tick(float DeltaTime) override;

	/** Shoots where our crosshair is */
	void AimTowardsCrosshair();

	bool GetSightRayHitLocation(FVector& OutHitLocation) const;
	
	// Calculates the direction of the crosshair in the world
	bool GetAimDirection(FVector2D ScreenLocation, FVector& AimDirection) const;
	// Ray trace from the crosshair position out to the world
	bool GetAimVectorHitLocation(FVector& HitLocation, FVector AimDirection) const;

	UPROPERTY(EditAnywhere, Category = "Crosshair")
	float CrossHairXLocation;
	UPROPERTY(EditAnywhere, Category = "Crosshair")
	float CrossHairYLocation;
	UPROPERTY(EditAnywhere)
	float AimLenght;
	FVector2D CrossHiarScreenLocation;
};
