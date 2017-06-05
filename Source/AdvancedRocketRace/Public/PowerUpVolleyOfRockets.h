// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PowerUpDeployable.h"
#include "PowerUpVolleyOfRockets.generated.h"

/**
 * 
 */
UCLASS()
class ADVANCEDROCKETRACE_API APowerUpVolleyOfRockets : public APowerUpDeployable
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	APowerUpVolleyOfRockets();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// There's no effect for this one
	virtual void Effect() override;
};
