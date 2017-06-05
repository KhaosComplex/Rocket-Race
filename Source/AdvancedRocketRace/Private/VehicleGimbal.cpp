// Fill out your copyright notice in the Description page of Project Settings.

#include "AdvancedRocketRace.h"
#include "VehicleGimbal.h"

void UVehicleGimbal::Rotate(float Degrees)
{
	SetRelativeRotation(FRotator(0, Degrees, 0));

	if (GetOwnerRole() < ROLE_Authority)
	{
		ServerRotate(Degrees);
	}
}

void UVehicleGimbal::ServerRotate_Implementation(float Degrees)
{
	Rotate(Degrees);
}

bool UVehicleGimbal::ServerRotate_Validate(float Degrees)
{
	return true;
}
bool UVehicleGimbal::GetParentComponent(USceneComponent *&Parent)
{
	TArray<USceneComponent*> Parents;
	GetParentComponents(Parents);
	Parent = Parents[0];
	return IsValid(Parent);
}