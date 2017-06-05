// Fill out your copyright notice in the Description page of Project Settings.

#include "AdvancedRocketRace.h"
#include "WheeledVehicleMovementComponent.h"
#include "VehiclePlayerController.h"
#include "VehicleImpactEffect.h"
#include "VehicleDustType.h"
#include "RocketWheeledVehicle.h"

ARocketWheeledVehicle::ARocketWheeledVehicle()
{
	VehicleAimingComponent = CreateDefaultSubobject<UVehicleAimingComponent>(FName("Aiming Component"));
	bTiresTouchingGround = false;
	SpringCompressionLandingThreshold = 250000.f;

	ImpactEffectNormalForceThreshold = 100000.f;
}

// Called when the game starts or when spawned
void ARocketWheeledVehicle::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ARocketWheeledVehicle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateWheelEffects(DeltaTime);
}

// Called when Vehicle hits
void ARocketWheeledVehicle::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalForce, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalForce, Hit);
	if (ImpactTemplate && NormalForce.SizeSquared() > FMath::Square(ImpactEffectNormalForceThreshold))
	{
		FTransform const SpawnTransform(HitNormal.Rotation(), HitLocation);
		AVehicleImpactEffect* EffectActor = GetWorld()->SpawnActorDeferred<AVehicleImpactEffect>(ImpactTemplate, SpawnTransform);
		if (EffectActor)
		{
			float DotBetweenHitAndUpRotation = FVector::DotProduct(HitNormal, GetMesh()->GetUpVector());
			EffectActor->HitSurface = Hit;
			EffectActor->HitForce = NormalForce;
			EffectActor->bWheelLand = DotBetweenHitAndUpRotation > 0.8f;
			UGameplayStatics::FinishSpawningActor(EffectActor, SpawnTransform);
		}
	}
	
	if (ImpactCameraShake)
	{
		AVehiclePlayerController* PC = Cast<AVehiclePlayerController>(Controller);
		if (PC != NULL && PC->IsLocalController())
		{
			PC->ClientPlayCameraShake(ImpactCameraShake, 1);
		}
	}
}

float ARocketWheeledVehicle::GetVehicleSpeed() const
{
	return (GetVehicleMovement()) ? FMath::Abs(GetVehicleMovement()->GetForwardSpeed()) : 0.0f;
}

// Aim the barrel towards the direction of the vector
void ARocketWheeledVehicle::AimAt(FVector HitLocation)
{
	VehicleAimingComponent->AimAt(HitLocation);
}

void ARocketWheeledVehicle::SetRocketLauncherReference(UVehicleRocketLauncher* RocketLauncherToSet)
{
	VehicleAimingComponent->SetRocketLauncherReference(RocketLauncherToSet);
}

void ARocketWheeledVehicle::SetRocketGimbalRefernce(UVehicleGimbal * GimbalToSet)
{
	VehicleAimingComponent->SetRocketGimbalReference(GimbalToSet);
}

bool ARocketWheeledVehicle::isVehicleOnGround()
{
	return bTiresTouchingGround;
}

void ARocketWheeledVehicle::SpawnNewWheelEffect(int WheelIndex)
{
	DustPSC[WheelIndex] = NewObject<UParticleSystemComponent>(this);
	DustPSC[WheelIndex]->bAutoActivate = true;
	DustPSC[WheelIndex]->bAutoDestroy = false;
	DustPSC[WheelIndex]->RegisterComponentWithWorld(GetWorld());
	DustPSC[WheelIndex]->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, GetVehicleMovement()->WheelSetups[WheelIndex].BoneName);
}

void ARocketWheeledVehicle::UpdateWheelEffects(float DeltaTime)
{
	if (GetVehicleMovement() && bTiresTouchingGround == false && LandingSound)	//we don't update bTiresTouchingGround until later in this function, so we can use it here to determine whether we're landing
	{
		float MaxSpringForce = GetVehicleMovement()->GetMaxSpringForce();
		if (MaxSpringForce > SpringCompressionLandingThreshold)
		{
			UGameplayStatics::PlaySoundAtLocation(this, LandingSound, GetActorLocation(), FMath::Clamp(GetVelocity().Size() / VelocityLengthSoundDivisor, 0.0f, 1.0f));
		}
	}

	bTiresTouchingGround = false;

	if (DustType && GetVehicleMovement() && GetVehicleMovement()->Wheels.Num() > 0)
	{
		const float CurrentSpeed = GetVehicleSpeed();
		for (int32 i = 0; i < ARRAY_COUNT(DustPSC); i++)
		{
			UPhysicalMaterial* ContactMat = GetVehicleMovement()->Wheels[i]->GetContactSurfaceMaterial();
			if (ContactMat != NULL)
			{
				bTiresTouchingGround = true;
			}

			UParticleSystem* WheelFX = DustType->GetDustFX(ContactMat, CurrentSpeed);

			const bool bIsActive = DustPSC[i] != NULL && !DustPSC[i]->bWasDeactivated && !DustPSC[i]->bWasCompleted;
			UParticleSystem* CurrentFX = DustPSC[i] != NULL ? DustPSC[i]->Template : NULL;
			
			if (WheelFX != NULL && (CurrentFX != WheelFX || !bIsActive))
			{
				if (DustPSC[i] == NULL || !DustPSC[i]->bWasDeactivated)
				{
					if (DustPSC[i] != NULL)
					{
						DustPSC[i]->SetActive(false);
						DustPSC[i]->bAutoDestroy = true;
					}
					SpawnNewWheelEffect(i);
				}
				DustPSC[i]->SetTemplate(WheelFX);
				DustPSC[i]->ActivateSystem();
			}
			else if (WheelFX == NULL && bIsActive)
			{
				DustPSC[i]->SetActive(false);
			}
		}
	}

	/*if (SkidAC != NULL)
	{
		FVector Vel = GetVelocity();
		bool bVehicleStopped = Vel.SizeSquared2D() < SkidThresholdVelocity*SkidThresholdVelocity;
		bool TireSlipping = GetVehicleMovement()->CheckSlipThreshold(LongSlipSkidThreshold, LateralSlipSkidThreshold);
		bool bWantsToSkid = bTiresTouchingGround && !bVehicleStopped && TireSlipping;

		float CurrTime = GetWorld()->GetTimeSeconds();
		if (bWantsToSkid && !bSkidding)
		{
			bSkidding = true;
			SkidAC->Play();
			SkidStartTime = CurrTime;
		}
		if (!bWantsToSkid && bSkidding)
		{
			bSkidding = false;
			SkidAC->FadeOut(SkidFadeoutTime, 0);
			if (CurrTime - SkidStartTime > SkidDurationRequiredForStopSound)
			{
				UGameplayStatics::PlaySoundAtLocation(this, SkidSoundStop, GetActorLocation());
			}
		}
	}*/
}