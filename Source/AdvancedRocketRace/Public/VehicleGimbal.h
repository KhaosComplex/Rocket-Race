// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "VehicleGimbal.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ADVANCEDROCKETRACE_API UVehicleGimbal : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	// Change the Yaw of the Gimbal
	void Rotate(float Degrees);

	UFUNCTION(Server, Reliable, WithValidation)
	void ServerRotate(float Degrees);

public:
	bool GetParentComponent(USceneComponent*& Parent);
};
