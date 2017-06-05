// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "VehicleRocketPawn.h"
#include "GameFramework/PlayerController.h"
#include "VehiclePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ADVANCEDROCKETRACE_API AVehiclePlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

private:
	// Return the controlled vehicle
	// Set the gimbal
	UFUNCTION(BlueprintCallable, Category = Vehicle)
		AVehicleRocketPawn* GetControlledVehicle() const;

private: 
	// Start the vehicle moving the barrel towards the crosshair
	void AimTowardsCrosshair();

	// Return an OUT parameter, true if hit landscape
	bool GetSightRayHitLocation(FVector& HitLocation) const;

	// Get the look direction relative to a 2d screen location
	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;

	// Get the hit location vector of a line trace fired from the camera through the crosshair into the world
	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;

	// Location of crosshair relative to the screen resolution
	UPROPERTY(EditAnywhere)
	float CrosshairLocationX = 0.5;

	// Location of crosshair relative to the screen resolution
	UPROPERTY(EditAnywhere)
	float CrosshairLocationY = 0.35;

	// Amount to line trace by
	UPROPERTY(EditAnywhere)
	float LineTraceRange = 1000000;

};
