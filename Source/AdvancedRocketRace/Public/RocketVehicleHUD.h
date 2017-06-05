// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "ObjectiveMarker.h"
#include "RocketVehicleHUD.generated.h"

/**
 * 
 */
UCLASS()
class ADVANCEDROCKETRACE_API ARocketVehicleHUD : public AHUD
{
	GENERATED_BODY()

public:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// The current Objective 
	UPROPERTY(BlueprintReadWrite, Category = Objectives)
	AObjectiveMarker* CurrentObjective;

	// Default HUD Icon for the powerup
	UPROPERTY(BlueprintReadWrite, Category = Icons)
	UTexture2D* CurrentPowerUpIcon;

};
