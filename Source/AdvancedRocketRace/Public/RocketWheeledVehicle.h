// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "VehicleAimingComponent.h"
#include "VehicleRocketLauncher.h"
#include "VehicleGimbal.h"
#include "VehicleTypes.h"
#include "WheeledVehicle.h"
#include "RocketWheeledVehicle.generated.h"

class UVehicleDustType;
class AVehicleImpactEffect;

UCLASS()
class ADVANCEDROCKETRACE_API ARocketWheeledVehicle : public AWheeledVehicle
{
	GENERATED_BODY()
	
public:
	// Begin Actor Overrides
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalForce, const FHitResult& Hit) override;

	/** get current speed */
	float GetVehicleSpeed() const;

public:
	// Aim the barrel towards the direction of the vector
	void AimAt(FVector HitLocation);

	// Set the rocket launcher mesh
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetRocketLauncherReference(UVehicleRocketLauncher* RocketLauncherToSet);

	// Set the gimbal
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetRocketGimbalRefernce(UVehicleGimbal * GimbalToSet);
	
	// Get the Rocket Launcher
	UVehicleRocketLauncher* GetRocketLauncher() const { return VehicleAimingComponent->GetRocketLauncher(); }

public:
	// Trigger this event if the player collided with an objective and is ready to score
	UFUNCTION(BlueprintImplementableEvent, Category = Scoring)
	void PlayerScored(AController* Player);

public:
	UFUNCTION(BlueprintCallable, Category = Runtime)
	bool isVehicleOnGround();

protected:
	/** dust FX config */
	UPROPERTY(Category = Effects, EditDefaultsOnly)
	UVehicleDustType* DustType;

	/** impact FX config */
	UPROPERTY(Category = Effects, EditDefaultsOnly)
	TSubclassOf<AVehicleImpactEffect> ImpactTemplate;

	/** The minimum amount of normal force that must be applied to the chassis to spawn an Impact Effect */
	UPROPERTY(EditAnywhere, Category = Effects)
	float ImpactEffectNormalForceThreshold;

	/** dust FX components */
	UPROPERTY(Transient)
	UParticleSystemComponent* DustPSC[4];

	/** sound attenuation */
	UPROPERTY(Category = Effects, EditDefaultsOnly)
	USoundCue* LandingSound;

	/** force divisor for playing sounds using HitNotify */
	UPROPERTY(EditDefaultsOnly, Category = Effects)
		float HitForceSoundDivisor = 2500000.0f;

	/** spring divisor for playing sounds using MaxSpring */
	UPROPERTY(EditDefaultsOnly, Category = Effects)
		float VelocityLengthSoundDivisor = 4000.0f;

	/** when entering new surface type, spawn new particle system, allowing old one to fade away nicely */
	void SpawnNewWheelEffect(int WheelIndex);

	/** update effects under wheels */
	void UpdateWheelEffects(float DeltaTime);

protected:
	/** whether tires are currently touching ground */
	bool bTiresTouchingGround;

	/** The amount of spring compression required during landing to play sound */
	UPROPERTY(Category = Effects, EditDefaultsOnly)
	float SpringCompressionLandingThreshold;

	/** camera shake on impact */
	UPROPERTY(Category = Effects, EditDefaultsOnly)
	TSubclassOf<UCameraShake> ImpactCameraShake;

protected:
	UPROPERTY(Category = Vehicle, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UVehicleAimingComponent* VehicleAimingComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Firing)
	FVector ProjectileVelocity = FVector(5500, 0, 0);

private:
	ARocketWheeledVehicle();
};
