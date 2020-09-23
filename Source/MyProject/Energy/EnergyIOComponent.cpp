// Fill out your copyright notice in the Description page of Project Settings.


#include "EnergyIOComponent.h"
#include "DrawDebugHelpers.h"
#include "../Macros.h"

// Sets default values for this component's properties
UEnergyIOComponent::UEnergyIOComponent() {
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UEnergyIOComponent::BeginPlay() {
	Super::BeginPlay();

	SetRelativeLocation(FVector::ZeroVector);
	// ..
	
}


// Called every frame
void UEnergyIOComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//float OutputDrawSum = 0;
	//for (auto Output : Outputs) {
	//	OutputDrawSum += Output->Draw;
	//}
	//Draw = FMath::Max(DefaultDraw, OutputDrawSum + DefaultDraw);
	//Usage = FMath::Min(Buffer, DefaultDraw);
	//Buffer = FMath::Max((float)0, Buffer - DefaultDraw);
	//TSet<UEnergyIOComponent*> Candidates;
	//Candidates.Append(Outputs);
	//while (Buffer > 0 && Candidates.Num() > 0) {
	//	float Avg = Buffer / Candidates.Num();
	//	Buffer = 0;
	//	for (auto Candidate : Candidates) {
	//		Buffer += FMath::Max((float)0, Avg - Candidate->Draw);
	//		Candidate->Buffer += FMath::Min(Avg, Candidate->Draw);
	//		if (Avg - Candidate->Draw >= 0) Candidates.Remove(Candidate);
	//	}
	//}
	// ...
	//int NeighborEnergySum = 0;

	FHitResult Hit;

	if (GetWorld()->LineTraceSingleByChannel(Hit, GetComponentLocation(), GetComponentLocation() + GetForwardVector() * 100, ECollisionChannel::ECC_WorldStatic)) {
		UEnergyIOComponent* EnergyIO = Hit.GetActor()->FindComponentByClass<UEnergyIOComponent>();

		if (EnergyIO != nullptr && !Connections.Contains(EnergyIO)) {
			AddConnection(EnergyIO);
			DEBUGMESSAGE("CONNECTED\n");
		}
	}

	DrawDebugDirectionalArrow(GetWorld(), GetComponentLocation(), GetComponentLocation() + GetForwardVector() * 100, 5, FColor::Red);

	DrawDebugDirectionalArrow(GetWorld(), GetComponentLocation(), GetComponentLocation() + GetUpVector() * Energy/50, 5, FColor::Red,false, -1, 10, 5);
	DrawDebugDirectionalArrow(GetWorld(), GetComponentLocation(), GetComponentLocation() - GetUpVector() * Usage, 5, FColor::Green, false, -1, 10, 5);

	//DrawDebugString(GetWorld(), GetComponentLocation() + GetUpVector() * 150, FString::SanitizeFloat(Energy), 0, FColor::Red, -1, false, 1);

	int NewEnergyDelta = 0;
	int InitialEnergy = Energy;
	for (auto Connection : Connections) {
		//NeighborEnergySum += Connection->Energy;
		//int Sign = Connection->Energy > Energy ? 1 : -1;
		//NewEnergyDelta += Sign * FMath::Abs(Connection->Energy - Energy);
		if (Consumption > 0) {

		} else if (Consumption < 0) {
			if (Connection->Consumption > 0 && Energy > 0) {
				if (Connection->Energy < Connection->Consumption) {


				}

			}
		} else {

		}
		
	}
	//Energy = FMath::Max(0, Energy + NewEnergyDelta);
	Usage = FMath::Min(Consumption, Energy);
	Energy = FMath::Max(0, Energy - Consumption);

	
}

void UEnergyIOComponent::AddConnection(UEnergyIOComponent* InEnergyIO) {
	//check(!Connections.Contains(InEnergyIO));
	//check(InEnergyIO != this);
	Connections.Add(InEnergyIO);
	InEnergyIO->Connections.Add(this);
}

void UEnergyIOComponent::RemoveConnection(UEnergyIOComponent* InEnergyIO) {
	//check(Connections.Contains(InEnergyIO));
	//check(InEnergyIO != this);
	Connections.Remove(InEnergyIO);
	//InEnergyIO->RemoveConnection(this);
}

void UEnergyIOComponent::AddOutput(UEnergyIOComponent* InEnergyIO) {
	check(!Outputs.Contains(InEnergyIO));
	check(InEnergyIO != this);
	Outputs.Add(InEnergyIO);
}

void UEnergyIOComponent::RemoveOutput(UEnergyIOComponent* InEnergyIO) {
	check(Outputs.Contains(InEnergyIO));
	check(InEnergyIO != this);
	Outputs.Remove(InEnergyIO);
}

