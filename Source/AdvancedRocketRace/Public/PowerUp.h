// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "PowerUp.generated.h"

UCLASS()
class ADVANCEDROCKETRACE_API APowerUp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APowerUp();

	// The total number of child actors this powerup uses
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Maintenance)
	uint8 TotalChildActors;

	// If InvalidChildActors == TotalChildActors then this actor is ready to be destroyed
	UPROPERTY(BlueprintReadWrite, Category = Maintenance)
	uint8 InvalidChildActors;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// The effect to be activated THIS HAS TO BE OVERRIDED
	virtual void Effect() PURE_VIRTUAL(APowerUp::Effect, );
	
	
};
