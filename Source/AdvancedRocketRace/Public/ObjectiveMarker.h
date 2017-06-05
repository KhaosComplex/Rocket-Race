// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ObjectiveMarker.generated.h"

UCLASS()
class ADVANCEDROCKETRACE_API AObjectiveMarker : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObjectiveMarker();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

public:
	// Hide the Actor
	UFUNCTION(BlueprintCallable, Category = Utilities)
	void Hide();

	// Show the Actor
	UFUNCTION(BlueprintCallable, Category = Utilities)
	void Show();

	// Blueprint event called when ready to be materialized
	UFUNCTION(BlueprintImplementableEvent, Category = Materialize)
	void PrepareForMaterialize();

	// Blueprint event called when ready to be materialized
	UFUNCTION(BlueprintImplementableEvent, Category = Materialize)
	void Materialize();

public:
	// Returns the static mesh (DEPRECATED)
	UStaticMesh* GetStaticMesh() const;

	void SetObjectiveManager(UObject* ObjectiveManager);

private:
	// The static mesh of the Objective
	UStaticMesh* StaticMesh;

	// Whether or not the Objective is currently triggered
	bool Triggered;

	// The reference to the scene's objective manager, so that we can call functions when a player collides with one.
	UObject* ObjectiveManager;

	// Determines if a player is what triggered the Objective
	UFUNCTION()
	void IfPlayerCapturedObjective(AActor* OverlappedActor, AActor* OtherActor);
	
};
