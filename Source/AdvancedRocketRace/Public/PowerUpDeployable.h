// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PowerUp.h"
#include "PowerUpDeployable.generated.h"

/**
 * 
 */
UCLASS()
class ADVANCEDROCKETRACE_API APowerUpDeployable : public APowerUp
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	APowerUpDeployable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	
};
