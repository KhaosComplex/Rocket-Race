// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "PowerUp.h"
#include "PowerUpComponent.generated.h"

USTRUCT(BlueprintType)
struct FPowerUpStruct
{
	GENERATED_BODY()

	// The list of all potential powerups that can be used
	UPROPERTY(EditAnywhere, Category = Powerups)
	TArray<TSubclassOf<APowerUp>> PowerUps;

	// HUD Icon for the powerup
	UPROPERTY(EditAnywhere, Category = Powerups)
	TArray<UTexture2D*> Icons;

	FPowerUpStruct() { }
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ADVANCEDROCKETRACE_API UPowerUpComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPowerUpComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Used to handle the icons and types of powerups available to each actor
	UPROPERTY(EditAnywhere, Category = PowerUps)
	FPowerUpStruct PowerUpStruct;

	// Update the current PowerUp on the client
	UFUNCTION()
	void OnRep_UpdateCurrentPowerUp();

	// Consume the current powerup and reset the state
	UFUNCTION(BlueprintCallable, Category = PowerUps)
	void ServerConsumePowerUp();

	// Consume the current powerup and reset the state
	UFUNCTION(BlueprintCallable, Category = PowerUps)
	UTexture2D* GetCurrentPowerUpIcon();

public:
	// Default HUD Icon for the powerup
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Icons)
	UTexture2D* DefaultPowerUpIcon;

private:
	// Random stream used for selecting the next random PowerUp
	FRandomStream RandomStream;


private:
	// Index of current PowerUp (-1 = ON CD)
	UPROPERTY(ReplicatedUsing = OnRep_UpdateCurrentPowerUp)
	int8 CurrentPowerUpIndex = -1;

protected:
	// The current PowerUp
	UPROPERTY(BlueprintReadOnly, Category = PowerUps)
	TSubclassOf<APowerUp> CurrentPowerUp;

private:
	// Time till first powerup will be revealed (DEFAULT = 10)
	UPROPERTY(EditAnywhere)
	uint16 PowerUpCooldown = 10;

	// Reveal the first powerup after a predetermined amount of time
	void ServerRequestPowerUp();
	
};
