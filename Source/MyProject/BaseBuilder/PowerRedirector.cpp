// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerRedirector.h"
#include "Globals.h"
#include "PanelSide.h"
#include "../Energy/EnergyIOComponent.h"

// Sets default values
APowerRedirector::APowerRedirector()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	StaticVisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = StaticVisualMesh;
	StaticVisualMesh->SetCollisionProfileName("InteractTrigger");

}

// Called when the game starts or when spawned
void APowerRedirector::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APowerRedirector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APowerRedirector::OnInteract_Implementation(UObject* TriggeredObject) {
	int PrevIndex = RotationIndex;
	FRotator CurrRot = StaticVisualMesh->GetRelativeRotation();
	FRotator NewRot = FRotator(0, CurrRot.Yaw + 90, 0);
	RotationIndex = (RotationIndex + 1) % 4;

	RotateEvent(CurrRot, FRotator(0, RotationIndex * 90, 0));
}

FText APowerRedirector::GetDescription() {
	return FText::FromString("Rotate (E)");
}

bool APowerRedirector::FindAndRegisterPanelSide(FVector SidesCenter, FVector Direction) {
	FHitResult Hit;
	if (GetWorld()->LineTraceSingleByChannel(Hit, SidesCenter, SidesCenter + Direction *5, COLLISION_PANELSIDE)) {
		PanelSide = Cast<UPanelSide>(Hit.GetComponent()->GetAttachParent());
	}
	if (PanelSide != nullptr) {
		if (RotationIndex % 2 == 1) {
			PanelSide->PowerConnections[0] = true;
			PanelSide->PowerConnections[1] = false;
			PanelSide->PowerConnections[2] = true;
			PanelSide->PowerConnections[3] = false;
		} else {
			PanelSide->PowerConnections[0] = false;
			PanelSide->PowerConnections[1] = true;
			PanelSide->PowerConnections[2] = false;
			PanelSide->PowerConnections[3] = true;
			
		}

	}
	return PanelSide != nullptr;
}

void APowerRedirector::UnRegisterPanelSide() {
	if (PanelSide != nullptr) {
		PanelSide->PowerConnections[0] = false;
		PanelSide->PowerConnections[1] = false;
		PanelSide->PowerConnections[2] = false;
		PanelSide->PowerConnections[3] = false;
	}
}