// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerColumn.h"
#include "PowerRedirector.h"
#include "Building.h"
#include "PanelSide.h"
#include "Panel.h"
#include "Components/BoxComponent.h"

// Sets default values
APowerColumn::APowerColumn()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;
	CapTop = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CapTop"));
	CapTop->SetupAttachment(RootComponent);
	CapBottom = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CapBottom"));
	CapBottom->SetupAttachment(RootComponent);

	CapTop->SetRelativeLocation(FVector::ZeroVector);
	CapBottom->SetRelativeLocation(FVector::ZeroVector);
	CapBottom->SetRelativeRotation(FRotator(180, 0, 0));

	InteractColliderA = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractColliderA"));
	InteractColliderA->SetCollisionProfileName("InteractTrigger");
	InteractColliderA->SetupAttachment(CapTop);
	InteractColliderB = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractColliderB"));
	InteractColliderB->SetCollisionProfileName("InteractTrigger");
	InteractColliderB->SetupAttachment(CapBottom);

}

// Called when the game starts or when spawned
void APowerColumn::BeginPlay()
{
	Super::BeginPlay();
	
	CylinderDefaultLocation = FVector::ZeroVector;

	PowerRedirectorUp = (APowerRedirector * ) GetWorld()->SpawnActor(PowerRedirectorBP);
	if (PowerRedirectorUp != nullptr) {
		PowerRedirectorUp->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
		PowerRedirectorUp->SetActorRelativeLocation(FVector(0, 0, 10));
	}
	PowerRedirectorDown = (APowerRedirector*)GetWorld()->SpawnActor(PowerRedirectorBP);
	if (PowerRedirectorUp != nullptr) {
		PowerRedirectorDown->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
		PowerRedirectorDown->SetActorRelativeLocation(FVector(0, 0, -10));
	}

}

// Called every frame
void APowerColumn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APowerColumn::OnInteract_Implementation(UObject* TriggeredObject, UObject* Interactor) {
	FVector NewLocation = CylinderDefaultLocation;
	FVector OldLocation = Root->GetRelativeLocation();
	int PrevOffset = CylinderOffset;
	if (TriggeredObject == InteractColliderA) if (CylinderOffset == 0) CylinderOffset = 1; else  CylinderOffset = 0;
	if (TriggeredObject == InteractColliderB) if (CylinderOffset == 0) CylinderOffset = -1; else  CylinderOffset = 0;
	NewLocation += FVector(0, 0, 32 * CylinderOffset);
	bool IsUp = (PrevOffset == 1);
	if (PrevOffset == 0) IsUp = (TriggeredObject == InteractColliderA);
	MoveCylinderEvent(OldLocation, NewLocation, IsUp);
	if(CylinderOffset != 0) UnregisterEnergyDiscs();
}

FText APowerColumn::GetDescription() {
	if (CylinderOffset != 0)
		return FText::FromString("Restore Power Column (E)");
	else 
		return FText::FromString("Extract Power Column (E)");	
}

void APowerColumn::RegisterEnergyDiscs() {
	if (CylinderOffset != 0) return;
	PowerRedirectorUp->FindAndRegisterPanelSide(GetActorLocation(), GetActorUpVector());
	PowerRedirectorDown->FindAndRegisterPanelSide(GetActorLocation(), -GetActorUpVector());
	ABuilding* Building = PowerRedirectorUp->PanelSide->Panel->Building;
	if (Building != nullptr) Building->FindPowerNetworks();

}

void APowerColumn::UnregisterEnergyDiscs() {
	PowerRedirectorUp->UnRegisterPanelSide();
	PowerRedirectorDown->UnRegisterPanelSide();
	ABuilding* Building = PowerRedirectorUp->PanelSide->Panel->Building;
	if (Building != nullptr) Building->FindPowerNetworks();
}

