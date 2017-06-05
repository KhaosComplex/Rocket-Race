// Fill out your copyright notice in the Description page of Project Settings.

#include "AdvancedRocketRace.h"
#include "Kismet/KismetMathLibrary.h"
#include "PowerUpComponent.h"


// Sets default values for this component's properties
UPowerUpComponent::UPowerUpComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UPowerUpComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Replicate to every client, no special condition required
	DOREPLIFETIME(UPowerUpComponent, CurrentPowerUpIndex);
}


// Called when the game starts
void UPowerUpComponent::BeginPlay()
{
	Super::BeginPlay();

	//Make the Random Stream
	RandomStream = FRandomStream();
	RandomStream.GenerateNewSeed();

	//Set a delay to reveal the first powerup after a predetermined time
	if (GetOwnerRole() == ROLE_Authority)
	{
		FTimerHandle UnusedHandle;
		GetWorld()->GetTimerManager().SetTimer(UnusedHandle, this, &UPowerUpComponent::ServerRequestPowerUp, PowerUpCooldown, false);
	}
	
}

// Called when a new powerup is selected
void UPowerUpComponent::OnRep_UpdateCurrentPowerUp()
{
	if (CurrentPowerUpIndex == -1)
	{
		CurrentPowerUp = nullptr;
	}
	else
	{
		CurrentPowerUp = PowerUpStruct.PowerUps[CurrentPowerUpIndex];
	}
}

// Reveal the first powerup after a predetermined amount of time
void UPowerUpComponent::ServerRequestPowerUp()
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		// Get a random powerup
		if (PowerUpStruct.PowerUps.Num() > 0)
		{
			CurrentPowerUpIndex = RandomStream.RandRange(0, PowerUpStruct.PowerUps.Num() - 1);
			CurrentPowerUp = PowerUpStruct.PowerUps[CurrentPowerUpIndex];
		}
	}
}

void UPowerUpComponent::ServerConsumePowerUp()
{
	if (GetOwnerRole() == ROLE_Authority)
	{
		// Get a random powerup
		CurrentPowerUpIndex = -1;
		CurrentPowerUp = nullptr;

		FTimerHandle UnusedHandle;
		GetWorld()->GetTimerManager().SetTimer(UnusedHandle, this, &UPowerUpComponent::ServerRequestPowerUp, PowerUpCooldown, false);
	}
}

UTexture2D * UPowerUpComponent::GetCurrentPowerUpIcon()
{
	if (CurrentPowerUpIndex == -1)
	{
		return DefaultPowerUpIcon;
	}

	return PowerUpStruct.Icons[CurrentPowerUpIndex];
}

