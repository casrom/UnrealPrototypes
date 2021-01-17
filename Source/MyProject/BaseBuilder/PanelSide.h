// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "PanelSide.generated.h"

class USpaceChunk;
class UEnergyStrip;
class UBoxComponent;
class APanel;

USTRUCT(BlueprintType)
struct FPanelSideData {
	GENERATED_BODY()
	UPROPERTY(VisibleAnywhere)
	FColor Color;
	FPanelSideData(): Color(FColor::White) {};
	FPanelSideData(FColor c) { Color = c; };
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT_API UPanelSide : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPanelSide();

	//UPROPERTY(EditDefaultsOnly)
	//USceneComponent* Root;

	UPROPERTY(EditDefaultsOnly)
	class UBoxComponent* Collider;

	UPROPERTY(VisibleAnywhere)
	FPanelSideData Data;

	UPROPERTY(VisibleAnywhere)
	TArray<UPanelSide*> Neighbors;

	TArray<int> RelativeSideIndices;

	UPROPERTY(VisibleAnywhere)
	USpaceChunk* SpaceChunk;

	UPROPERTY(VisibleAnywhere)
	int SideIndexOfChunk = -1;

	UPROPERTY()
	TArray<UEnergyStrip*> EnergyStrips;

	UPROPERTY(VisibleAnywhere)
	TArray<bool> PowerConnections;

	UPROPERTY()
	class UPowerNetwork* PowerNetwork;
	
	int ActivePowerConnectionNum = 0;
	
	bool DrawDebug = false;
	
	UPROPERTY()
	APanel* Panel;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	static void PropagateData(UPanelSide* Side, TSet<UPanelSide*>& Visited, FPanelSideData Data);
	static void FindPowerConnected(UPanelSide* Side, TSet<UPanelSide*>& Visited);

	bool CheckPowerConnection(int SideIndex);
	//void UpdateFlowEfficiency(float NewFlowEfficiency);
	//void RegisterSpaceChunk(USpaceChunk* SpaceChunk)
};
