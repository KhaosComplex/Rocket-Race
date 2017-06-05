// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "VehicleAimingComponent.generated.h"

class UVehicleRocketLauncher;
class UVehicleGimbal;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ADVANCEDROCKETRACE_API UVehicleAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UVehicleAimingComponent();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

public:
	// If the HitLocation != 0, call the MoveRocketLauncherTowards() function
	void AimAt(FVector HitLocation);

public:
	// Set the rocket launcher mesh
	void SetRocketLauncherReference(UVehicleRocketLauncher* RocketLauncherToSet);

	// Set the gimbal
	void SetRocketGimbalReference(UVehicleGimbal* GimbalToSet);

	UVehicleRocketLauncher* GetRocketLauncher() const { return RocketLauncher;  }

protected:
	// The rocket launcher mesh
	UPROPERTY(BlueprintReadWrite, Category = Setup)
	UVehicleRocketLauncher* RocketLauncher = nullptr;

	// The rocket launcher H Gimbal
	UPROPERTY(BlueprintReadWrite, Category = Setup)
	UVehicleGimbal* RocketGimbal = nullptr;

private:
	// Move the rocket launcher towards the aim direciton
	void MoveRocketLauncherTowards(FVector EndLocation);
};
