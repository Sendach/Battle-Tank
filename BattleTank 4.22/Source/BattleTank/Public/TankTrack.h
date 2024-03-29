// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = ("Tank Parts"), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetThrottle(float Throttle);

	// This is max force per track, in Newtons
	UPROPERTY(EditDefaultsOnly, Category = "Driving Force")
	float TrackMaxDrivingForce = 660000; // Tank weight (60 000) * Speed of a tank (40km/s or 11m/s)
};
