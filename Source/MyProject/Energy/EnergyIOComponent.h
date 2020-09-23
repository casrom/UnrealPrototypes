// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "EnergyIOComponent.generated.h"

USTRUCT()
struct FEnergyData {
	GENERATED_BODY()
	float Energy;
	FEnergyData() {}
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT_API UEnergyIOComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEnergyIOComponent();
	UPROPERTY(EditAnywhere)
	TSet<UEnergyIOComponent*> Inputs;
	UPROPERTY(EditAnywhere)
	TSet<UEnergyIOComponent*> Outputs;
	FEnergyData Data;

	UPROPERTY(EditAnywhere)
	TSet<UEnergyIOComponent*> Connections;

	bool bHoldsEnergy;
	UPROPERTY(EditAnywhere)
	int Energy;
	UPROPERTY(EditAnywhere)
	int Consumption;
	float Draw;
	float DefaultDraw;
	UPROPERTY(EditAnywhere)
	float Buffer;
	UPROPERTY(EditAnywhere)
	float Usage;
	float BufferMax;


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AddConnection(UEnergyIOComponent* InEnergyIO);
	void RemoveConnection(UEnergyIOComponent* InEnergyIO);

	void AddOutput(UEnergyIOComponent* InEnergyIO);
	void RemoveOutput(UEnergyIOComponent* InEnergyIO);

};
