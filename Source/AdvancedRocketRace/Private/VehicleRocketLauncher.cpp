// Fill out your copyright notice in the Description page of Project Settings.

#include "AdvancedRocketRace.h"
#include "VehicleRocketLauncher.h"


void UVehicleRocketLauncher::Elevate(float Degrees) 
{
	SetRelativeRotation(FRotator(Degrees, 0, 0));
	if (GetOwnerRole() < ROLE_Authority)
	{
		ServerElevate(Degrees);
	}
}

void UVehicleRocketLauncher::ServerElevate_Implementation(float Degrees)
{
	Elevate(Degrees);
}

bool UVehicleRocketLauncher::ServerElevate_Validate(float Degrees)
{
	return true;
}

bool UVehicleRocketLauncher::GetParentComponent(USceneComponent*& Parent)
{
	TArray<USceneComponent*> Parents;
	GetParentComponents(Parents);
	Parent = Parents[0];
	return IsValid(Parent);
}

