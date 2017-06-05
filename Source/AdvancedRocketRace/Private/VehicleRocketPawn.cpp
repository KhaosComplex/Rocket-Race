// Fill out your copyright notice in the Description page of Project Settings.

#include "AdvancedRocketRace.h"
#include "VehicleRocketPawn.h"

AVehicleRocketPawn::AVehicleRocketPawn()
{
	VehicleAimingComponent = CreateDefaultSubobject<UVehicleAimingComponent>(FName("Aiming Component"));
}

// Called when the game starts or when spawned
void AVehicleRocketPawn::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AVehicleRocketPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Aim the barrel towards the direction of the vector
void AVehicleRocketPawn::AimAt(FVector HitLocation)
{
	VehicleAimingComponent->AimAt(HitLocation);
}

void AVehicleRocketPawn::SetRocketLauncherReference(UVehicleRocketLauncher* RocketLauncherToSet)
{
	VehicleAimingComponent->SetRocketLauncherReference(RocketLauncherToSet);
}

void AVehicleRocketPawn::SetRocketGimbalRefernce(UVehicleGimbal * GimbalToSet)
{
	VehicleAimingComponent->SetRocketGimbalReference(GimbalToSet);
}
