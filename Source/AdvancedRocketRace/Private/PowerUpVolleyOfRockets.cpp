// Fill out your copyright notice in the Description page of Project Settings.

#include "AdvancedRocketRace.h"
#include "PowerUpVolleyOfRockets.h"




APowerUpVolleyOfRockets::APowerUpVolleyOfRockets()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void APowerUpVolleyOfRockets::BeginPlay()
{
	Super::BeginPlay();

}

// Does nothing for this powerup
void APowerUpVolleyOfRockets::Effect()
{

}
