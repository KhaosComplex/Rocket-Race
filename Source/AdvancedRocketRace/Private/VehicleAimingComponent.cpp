// Fill out your copyright notice in the Description page of Project Settings.

#include "AdvancedRocketRace.h"
#include "Kismet/KismetMathLibrary.h"
#include "VehicleRocketLauncher.h"
#include "VehicleGimbal.h"
#include "VehicleAimingComponent.h"


// Sets default values for this component's properties
UVehicleAimingComponent::UVehicleAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

void UVehicleAimingComponent::SetRocketLauncherReference(UVehicleRocketLauncher* RocketLauncherToSet)
{
	RocketLauncher = RocketLauncherToSet;
}

void UVehicleAimingComponent::SetRocketGimbalReference(UVehicleGimbal* GimbalToSet)
{
	RocketGimbal = GimbalToSet;
}
// Called when the game starts
void UVehicleAimingComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UVehicleAimingComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
}

void UVehicleAimingComponent::AimAt(FVector HitLocation)
{
	// Protect RocketLauncher & Gimbal pointer
	if (RocketLauncher != nullptr && RocketGimbal != nullptr) 
	{
		if (HitLocation != FVector(0))
		{
			MoveRocketLauncherTowards(HitLocation);
		}
	}
}

void UVehicleAimingComponent::MoveRocketLauncherTowards(FVector EndLocation)
{
	// Get the parent component from the Gimbal
	USceneComponent* Parent;
	if (RocketGimbal->GetParentComponent(Parent))
	{
		// Get the HitLocation relative to the local space of the vehicle
		FVector EndLocationInLocalSpace = UKismetMathLibrary::InverseTransformLocation(Parent->GetComponentTransform(), EndLocation);
		FVector RocketGimbalLocalLocation = UKismetMathLibrary::InverseTransformLocation(Parent->GetComponentTransform(), RocketGimbal->GetComponentLocation());

		// Get the look at rotation for the Gimbal/Rocket Launcher
		FRotator LookAtRotator = UKismetMathLibrary::FindLookAtRotation(RocketGimbalLocalLocation, EndLocationInLocalSpace);

		// Finally, tell the components to rotate properly
		RocketGimbal->Rotate(LookAtRotator.Yaw);
		RocketLauncher->Elevate(LookAtRotator.Pitch);
	}
}
