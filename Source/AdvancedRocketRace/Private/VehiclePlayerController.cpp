// Fill out your copyright notice in the Description page of Project Settings.

#include "AdvancedRocketRace.h"
#include "VehiclePlayerController.h"

// Called when the game starts or when spawned
void AVehiclePlayerController::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AVehiclePlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Role >= ROLE_AutonomousProxy && IsLocalController())
	{
		AimTowardsCrosshair();
	}
}

AVehicleRocketPawn* AVehiclePlayerController::GetControlledVehicle() const
{
	return Cast<AVehicleRocketPawn>(GetPawn());
}

void AVehiclePlayerController::AimTowardsCrosshair()
{
	// If no player owned vehicle was spawned into the world, just return
	if (!GetControlledVehicle()) { return; }

	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation))
	{
		GetControlledVehicle()->AimAt(HitLocation);
	}
}

// Get world location of linetrace through crosshair, true if hits landscape
bool AVehiclePlayerController::GetSightRayHitLocation(FVector& HitLocation) const
{
	// Find the crosshair position in pixel coordinates
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);
	FVector2D ScreenLocation = FVector2D(ViewportSizeX * CrosshairLocationX, ViewportSizeY * CrosshairLocationY);

	// "De-project" the screen position of the crosshair to a world direction
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		// Line-trace along that LookDirection, and see what we hit (up to max range)
		GetLookVectorHitLocation(LookDirection, HitLocation);
	}

	return true;
}

bool AVehiclePlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	/*const FName TraceTag("MyTraceTag");
	GetWorld()->DebugDrawTraceTag = TraceTag;
	FCollisionQueryParams CollisionParams;
	CollisionParams.TraceTag = TraceTag;*/

	FHitResult HitResult;
	FVector StartLocation = PlayerCameraManager->GetCameraLocation();
	FVector EndLocation = StartLocation + (LookDirection * LineTraceRange);
	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECollisionChannel::ECC_GameTraceChannel2))
	{
		HitLocation = HitResult.Location;
		return true;
	}
	HitLocation = FVector(0);
	return false; // Line trace didn't succeed
}

bool AVehiclePlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation; // Not used
	return  DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraWorldLocation, LookDirection);
}
