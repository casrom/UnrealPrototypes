// Fill out your copyright notice in the Description page of Project Settings.


#include "Building.h"
#include "Panel.h"
#include "PanelSide.h"

// Sets default values
ABuilding::ABuilding()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Enclosure = CreateDefaultSubobject<USpaceEnclosure>("Enclosure");

}

// Called when the game starts or when spawned
void ABuilding::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABuilding::AddPanel(APanel& Panel) {
	check(!Panels.Contains(&Panel));

	Panel.Building = this;
	Panel.AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
	Enclosure->Expand(Panel);
	Panels.Add(&Panel);
	PanelSides.Add(Panel.Sides[0]);
	PanelSides.Add(Panel.Sides[1]);

}

void ABuilding::FindPowerNetworks() {
	PowerNetworks.Empty();
	for (auto PanelSide : PanelSides) {
		PanelSide->PowerNetwork = nullptr;
	}
	TSet<UPanelSide*> Unvisited;
	Unvisited.Append(PanelSides);
	//DEBUGMESSAGE("%d\n", PowerNetworks.Num());
	int Iter = 0;
	while (Iter < 100 && Unvisited.Num() > 0 ) {
		Iter++;
		UPanelSide* Start = nullptr;
		for (auto P : Unvisited) {
			Start = P;
			break;
		}
		TSet<UPanelSide*> Query;
		UPanelSide::FindPowerConnected(Start, Query);
		if (Query.Num() > 0) {
			UPowerNetwork* Network = NewObject<UPowerNetwork>();
			Network->PanelSides = Query;
			Network->Power = 0;
			for (auto PanelSide : Query) {
				PanelSide->PowerNetwork = Network;
			}
			PowerNetworks.Add(Network);
		}
		DEBUGMESSAGE("Q = %d, U = %d, Iter = %d\n", Query.Num(), Unvisited.Num(), Iter);
		Unvisited = Unvisited.Difference(Query);
	}

	DEBUGMESSAGE("%d\n", PowerNetworks.Num());
}