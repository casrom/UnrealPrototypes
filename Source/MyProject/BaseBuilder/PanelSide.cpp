// Fill out your copyright notice in the Description page of Project Settings.


#include "PanelSide.h"
#include "Panel.h"
#include "EnergyStrip.h"
#include "SpaceChunk.h"
#include "Globals.h"
#include "Components/BoxComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UPanelSide::UPanelSide()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	EnergyStrips.Init(nullptr, 4);
	PowerConnections.Init(false, 4);
	Neighbors.Init(nullptr, 5);
	RelativeSideIndices.Init(-1, 4);

	Collider = CreateDefaultSubobject<UBoxComponent>(MakeUniqueObjectName(this, UBoxComponent::StaticClass(), "SideCollider"));
	Collider->SetupAttachment(this);
	Collider->SetRelativeLocation(FVector::ZeroVector);
	FVector S = FVector(GRID_SIZE, GRID_SIZE, 1);
	float Margin = 10 + 0.1;
	Collider->InitBoxExtent(S/2 - FVector(Margin, Margin, 0));
	Collider->SetCollisionProfileName("Trigger");
	Collider->SetCollisionResponseToChannel(COLLISION_PANELSIDE, ECR_Block);
	Collider->ComponentTags.Add("PanelSideCollider");

}


// Called when the game starts
void UPanelSide::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UPanelSide::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (DrawDebug)
		DrawDebugBox(GetWorld(), GetComponentLocation(), FVector::OneVector * 2, Data.Color, false, -1, 10);

	for (int i = 0; i < 4; i++) {
		if (DrawDebug && Neighbors[i] != nullptr && RelativeSideIndices[i] != -1)
			DrawDebugDirectionalArrow(GetWorld(), GetComponentTransform().TransformPosition(APanel::IndexToConnectorLocation(i) * GRID_SIZE / 2.4), Neighbors[i]->GetComponentTransform().TransformPosition(APanel::IndexToConnectorLocation(RelativeSideIndices[i]) * GRID_SIZE / 2.4), 10, FColor::Red, false, -1, 10, 1);


		UEnergyStrip* EnergyStrip = EnergyStrips[i];
		if (EnergyStrip != nullptr) {
			if (DrawDebug && EnergyStrip->StaticVisualMesh!=nullptr)
				DrawDebugDirectionalArrow(GetWorld(), GetComponentTransform().TransformPosition(APanel::IndexToConnectorLocation(i) * GRID_SIZE / 2.4), EnergyStrip->StaticVisualMesh->GetComponentLocation() + EnergyStrip->StaticVisualMesh->GetForwardVector()*10 + EnergyStrip->StaticVisualMesh->GetUpVector() * 10, 10, FColor::Blue, false, -1, 10, 1);
			if (CheckPowerConnection(i)) EnergyStrip->ActivateEnergyStrip(PowerNetwork);
			else EnergyStrip->DeactivateEnergyStrip();
			
		}
	}
}


void UPanelSide::PropagateData(UPanelSide* Side, TSet<UPanelSide*>& Visited, FPanelSideData Data) {
	//DEBUGMESSAGE("P\n");
	if (Visited.Contains(Side)) {
		return;
	} else {
		Visited.Add(Side);

		Side->Data = Data;
		for (int i = 0; i < 4; i++) {
			PropagateData(Side->Neighbors[i], Visited, Data);
		}
	}
}

void UPanelSide::FindPowerConnected(UPanelSide* Side, TSet<UPanelSide*>& Visited) {
	//DEBUGMESSAGE("P\n");
	if (Visited.Contains(Side) || Side == nullptr) {
		return;
	} else {
		Visited.Add(Side);

		for (int i = 0; i < 4; i++) {
			if (Side->CheckPowerConnection(i))
				FindPowerConnected(Side->Neighbors[i], Visited);
		}
	}
}


bool UPanelSide::CheckPowerConnection(int SideIndex) {
	if (RelativeSideIndices[SideIndex] != -1 && Neighbors[SideIndex] != nullptr) {
		return PowerConnections[SideIndex] && Neighbors[SideIndex]->PowerConnections[RelativeSideIndices[SideIndex]];
	}
	return false;
}

//void UPanelSide::UpdateFlowEfficiency(float NewFlowEfficiency) {
//	if (SpaceChunk != nullptr && SideIndexOfChunk != -1) SpaceChunk->FlowEfficiencies[SideIndexOfChunk] = NewFlowEfficiency;
//}
//
//
//void UPanelSide::RegisterSpaceChunk(USpaceChunk* SpaceChunk) {
//	FVector PanelSideRelativeLocation = SpaceChunk->GetComponentTransform().InverseTransformPosition(GetComponentLocation());
//	PanelSideRelativeLocation.Normalize();
//	int PanelIndex = USpaceChunk::RelativeLocationToIndex(PanelSideRelativeLocation);
//	if (PanelIndex != -1) {
//		SpaceChunk->FlowEfficiencies[PanelIndexA] = FlowEfficiency;
//		PanelSides[1]->SideIndexOfChunk = PanelIndexA;
//		//DEBUGMESSAGE("SetFLOWA = %d, %s\n", PanelIndexA, *PanelRelativeLocationA.ToString());
//	}
//}
