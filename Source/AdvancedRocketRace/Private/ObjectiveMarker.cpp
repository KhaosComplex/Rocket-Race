// Fill out your copyright notice in the Description page of Project Settings.

#include "AdvancedRocketRace.h"
#include "ObjectiveMarker.h"
#include "ReactsToObjectiveCapture.h"
#include "VehicleRocketPawn.h"


// Sets default values
AObjectiveMarker::AObjectiveMarker()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AObjectiveMarker::BeginPlay()
{
	Super::BeginPlay();

	//Setup the overlap event
	OnActorBeginOverlap.AddDynamic(this, &AObjectiveMarker::IfPlayerCapturedObjective);

	//Get static mesh;
	TArray<UStaticMeshComponent*> Components;
	GetComponents<UStaticMeshComponent>(Components);
	UStaticMeshComponent* StaticMeshComponent = Components[0];
	StaticMesh = StaticMeshComponent->GetStaticMesh();
	Hide();
}

// Called every frame
void AObjectiveMarker::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

void AObjectiveMarker::Hide() {
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
}

void AObjectiveMarker::Show() {
	SetActorHiddenInGame(false);
	SetActorEnableCollision(true);
}

UStaticMesh* AObjectiveMarker::GetStaticMesh() const
{
	return StaticMesh;
}

void AObjectiveMarker::SetObjectiveManager(UObject* WorldObjectiveManager)
{
	ObjectiveManager = WorldObjectiveManager;
}

void AObjectiveMarker::IfPlayerCapturedObjective(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor->ActorHasTag("Player"))
	{
		IReactsToObjectiveCapture* ObjectiveInterface = Cast<IReactsToObjectiveCapture>(ObjectiveManager);
		if (ObjectiveInterface)
		{
			ObjectiveInterface->ReactToObjectiveCapture();
		}
		if (Role == ROLE_Authority)
		{
			AVehicleRocketPawn* Player = Cast<AVehicleRocketPawn>(OtherActor);
			if (Player)
			{
				Player->PlayerScored(Player->GetController());
			}
		}
	}
}
