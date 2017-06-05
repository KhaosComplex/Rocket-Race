// Fill out your copyright notice in the Description page of Project Settings.

#include "AdvancedRocketRace.h"
#include "ObjectiveManager.h"


// Sets default values
AObjectiveManager::AObjectiveManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AObjectiveManager::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Replicate to every client, no special condition required
	DOREPLIFETIME(AObjectiveManager, CurrentObjectiveIndex);
}

// Called when the game starts or when spawned
void AObjectiveManager::BeginPlay()
{
	Super::BeginPlay();

	//Make the Random Stream
	RandomStream = FRandomStream();
	RandomStream.GenerateNewSeed();

	if (Role == ROLE_Authority)
	{
		//Set a delay to reveal the first objective after a predetermined time
		FTimerHandle UnusedHandle;
		GetWorldTimerManager().SetTimer(UnusedHandle, this, &AObjectiveManager::ServerRevealFirstObjective, TimeTillFirstObjective, false);
	}

	for (AObjectiveMarker* Objective : Objectives)
	{
		Objective->SetObjectiveManager(this);
		Objective->SetActorEnableCollision(false);
	}
}

// Called every frame
void AObjectiveManager::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

void AObjectiveManager::ServerRevealFirstObjective()
{
	if (Role == ROLE_Authority)
	{
		//Set the first waypoint
		if (Objectives.Num() != 0)
		{
			CurrentObjectiveIndex = RandomStream.RandRange(0, Objectives.Num() - 1);
			CurrentObjective = Objectives[CurrentObjectiveIndex];
			CurrentObjective->SetActorEnableCollision(true);
			CurrentObjective->Show();
		}
	}
}

void AObjectiveManager::UpdateCurrentObjective()
{
	if (Role == ROLE_Authority)
	{
		CurrentObjective->SetActorEnableCollision(false);
		ObjectivesNotAllowed.Add(CurrentObjectiveIndex);
		CurrentRandomValue = RandomStream.RandRange(0, Objectives.Num() - 1);

		//If all objectives have been cycled through, empty the list and restart
		if (ObjectivesNotAllowed.Num() == Objectives.Num())
		{
			ObjectivesNotAllowed.Empty();
			ObjectivesNotAllowed.Add(CurrentObjectiveIndex);
			CurrentRandomValue = CurrentObjectiveIndex;
		}

		//While our random value is still one we cannot use, set a new random value
		while (ObjectivesNotAllowed.Contains(CurrentRandomValue))
		{
			CurrentRandomValue = RandomStream.RandRange(0, Objectives.Num() - 1);
		}

		// Once we found one we can use, set it so all the clients can update
		CurrentObjectiveIndex = CurrentRandomValue;

		//Set the original objective to materialize
		CurrentObjective->Materialize();

		//Finally, set the new current objective
		CurrentObjective = Objectives[CurrentObjectiveIndex];
		CurrentObjective->SetActorEnableCollision(true);
		CurrentObjective->PrepareForMaterialize();
		CurrentObjective->Show();
	}
}

void AObjectiveManager::OnRep_UpdateCurrentObjective()
{
	// Materialize the original Objective
	if (CurrentObjective)
	{
		CurrentObjective->SetActorEnableCollision(false);
		CurrentObjective->Materialize();
	}

	// Set the new Objective
	CurrentObjective = Objectives[CurrentObjectiveIndex];
	CurrentObjective->SetActorEnableCollision(true);
	CurrentObjective->PrepareForMaterialize();
	CurrentObjective->Show();
}

void AObjectiveManager::ReactToObjectiveCapture()
{
	UpdateCurrentObjective();
}

AObjectiveMarker* AObjectiveManager::GetCurrentObjective() const
{
	return CurrentObjective;
}
