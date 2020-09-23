// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EnergyUserInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UEnergyUserInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Energy user use EnergyIO Components to transfer and modify energy
 */
class MYPROJECT_API IEnergyUserInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
};
