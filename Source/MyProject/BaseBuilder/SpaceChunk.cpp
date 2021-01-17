// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceChunk.h"
#include "DrawDebugHelpers.h"
#include "Globals.h"
#include "GameFramework/Character.h"
#include "../MyProjectCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/BoxComponent.h"

#include "../Macros.h"


// Sets default values for this component's properties
USpaceChunk::USpaceChunk()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<UBoxComponent>(TEXT("SpaceCollider"));
	Collider->SetBoxExtent(FVector::OneVector * GRID_SIZE / 2);
	Collider->SetRelativeLocation(FVector::ZeroVector);
	Collider->SetCollisionProfileName("SpaceChunk");
	Collider->SetGenerateOverlapEvents(true);
	Collider->SetupAttachment(this);
	Data.Pressure = 0;
	Neighbors.Init(nullptr, 6);
	FlowEfficiencies.Init(1, 6);
}


// Called when the game starts
void USpaceChunk::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void USpaceChunk::Initialize(FIntVector InRelativeLocation) {
	Center = InRelativeLocation;
	SetRelativeLocation((FVector)InRelativeLocation);
	//this->RegisterComponent();
	Collider->RegisterComponent();

	Data.Pressure = 100;
}


// Called every frame
void USpaceChunk::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector NetForce = FVector::ZeroVector;
	float NewPressureDelta = 0;
	for (int i = 0; i < 6; i++) {
		USpaceChunk* Neighbor = Neighbors[i];
		float FlowEfficiency = FlowEfficiencies[i];
		float NeighborPressure = 0;
		if (Neighbor != nullptr) NeighborPressure = Neighbor->Data.Pressure;

		NetForce += IndexToRelativeLocation(i) * (Data.Pressure - NeighborPressure) * FlowEfficiencies[i];
		int Sign = NeighborPressure > Data.Pressure ? 1 : -1;
		NewPressureDelta += Sign * FMath::Min(FMath::Abs(NeighborPressure - Data.Pressure) * FlowEfficiency , MaxFlowRate);
	}

	Data.Pressure += NewPressureDelta;
	if (Data.Pressure < 0) Data.Pressure = 0;
	Data.Color = FColor(Data.Pressure/100 * 255, 0, 0);
	FVector ForceAngle = NetForce;
	ForceAngle.Normalize();

	if (NetForce.SizeSquared() > 0) {
		//DEBUGMESSAGE("WIND\n");
		TArray<AActor*>  Characters;
		Collider->GetOverlappingActors(Characters, ACharacter::StaticClass());
		for (auto Character : Characters) {
			AMyProjectCharacter* Player = Cast<AMyProjectCharacter>(Character);
			if (Player != nullptr) {
				DEBUGMESSAGE("WIND\n");
				FVector ComponentAngle = GetComponentTransform().InverseTransformPosition(Player->GetActorLocation());
				//Player->EnableSimulatePhysics();
				Player->GetCharacterMovement()->AddForce(NetForce.Size() * (ForceAngle*GRID_SIZE - ComponentAngle) / 5);

			}
		}

		TArray<UPrimitiveComponent*> Components;
		Collider->GetOverlappingComponents (Components);
		for (auto MeshComponent : Components) {
			//DEBUGMESSAGE(".%s\n", *MeshComponent->GetFName().ToString());

			FVector ComponentAngle = GetComponentTransform().InverseTransformPosition(MeshComponent->GetComponentLocation());
			ComponentAngle.Normalize();
			if (MeshComponent->IsSimulatingPhysics())
				MeshComponent->AddForce(NetForce.Size() * (ForceAngle - ComponentAngle) * 1000);
		}
	}

	if (Collider != NULL) {
	//	//DrawDebugBox(GetWorld(), GetComponentLocation(), Collider->GetUnscaledBoxExtent() * 0.9, GetComponentRotation().Quaternion(), FColor::Green, false);
		//DrawDebugBox(GetWorld(), GetComponentLocation(), Collider->GetUnscaledBoxExtent() * 0.5, GetComponentRotation().Quaternion(), Data.Color, false, 10);
		FVector StartLocation = GetComponentLocation();
		FVector EndLocation = StartLocation + NetForce;
		//*DrawDebugDirectionalArrow(GetWorld(), StartLocation, EndLocation, 10, FColor::Red, false, -1, 10, 5);
	//	//DrawDebugString(GetWorld(), GetComponentLocation(), TEXT("XXX"), (AActor*)0, FColor::Red);
	}

	for (int i = 0; i < 6; i++) {
		//*DrawDebugBox(GetWorld(), GetComponentLocation() + IndexToRelativeLocation(i) * 20, FVector::OneVector * 5, FColor(FlowEfficiencies[i] * 255, 0, 0));
	}

	////DEBUGMESSAGE("%s\n", *pair.Value->Box.Extent.ToString());
	//for (int i = 0; i < 6; i++) {
	//	if (Neighbors[i] != nullptr) {
	//		DrawDebugDirectionalArrow(GetWorld(), GetComponentLocation(), Neighbors[i]->GetComponentLocation(), 5, FColor::Red);
	//	}
	//}
}

void USpaceChunk::FindConnectedChunks(TSet<USpaceChunk*>& OutChunks) {
	OutChunks.Add(this);
	for (USpaceChunk* Neighbor : Neighbors) {
		if (!OutChunks.Contains(Neighbor)) Neighbor->FindConnectedChunks(OutChunks);
	}
}


FVector USpaceChunk::IndexToRelativeLocation(int Index) {
	check(Index >= 0 && Index < 6);
	switch (Index) {
	case 0: return FVector::UpVector;
	case 1: return FVector::ForwardVector;
	case 2: return FVector::RightVector;
	case 3: return -FVector::ForwardVector;
	case 4: return -FVector::RightVector;
	case 5: return -FVector::UpVector;
	default: return FVector::ZeroVector;
	}
}

int USpaceChunk::RelativeLocationToIndex(FVector Location) {
	for (int i = 0; i < 6; i++) {
		if (Location.Equals(IndexToRelativeLocation(i), 0.9)) return i;
	}
	return -1;
}