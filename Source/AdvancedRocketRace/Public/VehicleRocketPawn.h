// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "VehicleAimingComponent.h"
#include "VehicleRocketLauncher.h"
#include "VehicleGimbal.h"
#include "VehiclePhysicsActor.h"
#include "VehicleRocketPawn.generated.h"

/**
 * 
 */
UCLASS()
class ADVANCEDROCKETRACE_API AVehicleRocketPawn : public AVehiclePhysicsActor
{
	GENERATED_BODY()

// Default inherited methods
public:
	// Begin Actor Overrides
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

// Vehicle Aiming Mechanics
public:
	// Aim the barrel towards the direction of the vector
	void AimAt(FVector HitLocation);

	// Set the rocket launcher mesh
	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetRocketLauncherReference(UVehicleRocketLauncher* RocketLauncherToSet);

	// Set the gimbal
	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetRocketGimbalRefernce(UVehicleGimbal * GimbalToSet);

	// Get the Rocket Launcher
	UVehicleRocketLauncher* GetRocketLauncher() const { return VehicleAimingComponent->GetRocketLauncher(); }

protected:
	UPROPERTY(Category = Vehicle, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UVehicleAimingComponent* VehicleAimingComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Firing)
		FVector ProjectileVelocity = FVector(5500, 0, 0);

// Scoring mechanics
public:
	// Trigger this event if the player collided with an objective and is ready to score
	UFUNCTION(BlueprintImplementableEvent, Category = Scoring)
		void PlayerScored(AController* Player);

private:
	AVehicleRocketPawn();
};
