// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "VehicleRocketLauncher.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ADVANCEDROCKETRACE_API UVehicleRocketLauncher : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// Change the Pitch of the Rocket Launcher
	void Elevate(float Degrees);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerElevate(float Degrees);

public:
	bool GetParentComponent(USceneComponent*& Parent);
	
};
