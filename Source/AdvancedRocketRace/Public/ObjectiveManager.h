// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ObjectiveMarker.h"
#include "ReactsToObjectiveCapture.h"
#include "ObjectiveManager.generated.h"

UCLASS()
class ADVANCEDROCKETRACE_API AObjectiveManager : public AActor, public IReactsToObjectiveCapture
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObjectiveManager();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Update the current objective to a new one
	void UpdateCurrentObjective();

	// Update the current objective on the client
	UFUNCTION()
	void OnRep_UpdateCurrentObjective();

public:
	virtual void ReactToObjectiveCapture() override;

public:
	// Returns the current Objective
	UFUNCTION(BlueprintCallable, Category = Objectives)
	AObjectiveMarker* GetCurrentObjective() const;

private:
	// Random stream used for selecting the next random Objective
	FRandomStream RandomStream;

	// The current random value to test against
	uint8 CurrentRandomValue;

private:
	// List of all possible Objectives
	UPROPERTY(EditAnywhere)
	TArray<AObjectiveMarker*> Objectives;

	// Index of current Objective
	UPROPERTY(transient, ReplicatedUsing = OnRep_UpdateCurrentObjective)
	int8 CurrentObjectiveIndex = -1;

	// Current Objective
	AObjectiveMarker* CurrentObjective;

	// Objectives not allowed to be selected currently
	TArray<int8> ObjectivesNotAllowed;

private:
	// Time till first objective will be revealed (DEFAULT = 10)
	UPROPERTY(EditAnywhere)
	uint16 TimeTillFirstObjective = 10;

	// Reveal the first objective after a predetermined amount of time
	void ServerRevealFirstObjective();
};
