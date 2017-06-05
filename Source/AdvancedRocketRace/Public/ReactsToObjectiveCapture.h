// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ReactsToObjectiveCapture.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UReactsToObjectiveCapture : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

/**
 * 
 */
class ADVANCEDROCKETRACE_API IReactsToObjectiveCapture
{
	GENERATED_IINTERFACE_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void ReactToObjectiveCapture() = 0;
	
};
