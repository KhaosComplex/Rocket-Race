// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PowerUp.h"
#include "PowerUpBuff.generated.h"

/**
 * 
 */
UCLASS()
class ADVANCEDROCKETRACE_API APowerUpBuff : public APowerUp
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APowerUpBuff();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Duration of buff
	uint32 Duration;

	// Whether or not the buff can stack
	bool CanStack;

	// The Actor to be affected (Can be self)
	AActor* AffectedActor;
	
	
	
};
