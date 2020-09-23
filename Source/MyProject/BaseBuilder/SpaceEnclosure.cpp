// Fill out your copyright notice in the Description page of Project Settings.


#include "SpaceEnclosure.h"
#include "../Macros.h"
#include "DrawDebugHelpers.h"
#include "Panel.h"
#include "SpaceChunk.h"

// Sets default values for this component's properties
USpaceEnclosure::USpaceEnclosure()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	BBox.Init();

}


// Called when the game starts
void USpaceEnclosure::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

//Essentially finding connected components
void USpaceEnclosure::CalculateSubenclosures() {
	TSet<USpaceChunk*> WorkingSet;
	WorkingSet.Append(Chunks);
	while(WorkingSet.Num() != 0) {
		FSpaceChunkSet ChunkSet;
		for (USpaceChunk* RandomChunk : WorkingSet) {
			RandomChunk->FindConnectedChunks(ChunkSet.SpaceChunks);
			break;
		}
		WorkingSet.Difference(ChunkSet.SpaceChunks);
	}
}


// Called every frame
void USpaceEnclosure::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector Extend = BBox.GetExtent();
	FVector Center = BBox.GetCenter();
	//DEBUGMESSAGE("%s\n", *Extend.ToString());
	DrawDebugBox(GetWorld(), GetComponentLocation() + Center, Extend, GetComponentRotation().Quaternion(), FColor::Red, false);

	//for (const TPair<FIntVector, USpaceChunk*>& pair : Chunks) {
	//	DrawDebugBox(GetWorld(), GetComponentTransform().TransformPosition((FVector)pair.Key), FVector::OneVector * GRID_SIZE/2 * 0.9 , GetComponentRotation().Quaternion(), FColor::Green, false);
	//	//DEBUGMESSAGE("%s\n", *pair.Value->Box.Extent.ToString());

	//	
	//	for (int i = 0; i < 6; i++) {
	//		if (pair.Value->Neighbors[i] != nullptr) {
	//			DrawDebugDirectionalArrow(GetWorld(), GetComponentTransform().TransformPosition((FVector)pair.Key), GetComponentTransform().TransformPosition((FVector)pair.Value->Neighbors[i]->Center), 5, FColor::Red);
	//		}
	//	}
	//}
}

void USpaceEnclosure::Initialize(FTransform InTransform, FVector InMinCorner, FVector InMaxCorner) {
    FBox B = FBox(InMinCorner, InMaxCorner);
    BBox = B;
    DEBUGMESSAGE("C%s\n", *BBox.ToString());
}

void USpaceEnclosure::Expand(APanel& Panel) {
	FIntVector A = (FIntVector)GetComponentTransform().InverseTransformPosition(Panel.GetActorLocation() - Panel.GetActorUpVector() * GRID_SIZE / 2);
	FIntVector B = (FIntVector)GetComponentTransform().InverseTransformPosition(Panel.GetActorLocation() + Panel.GetActorUpVector() * GRID_SIZE / 2);
	FIntVector Max = (FIntVector)GetComponentTransform().InverseTransformPosition(Panel.GetActorLocation() + Panel.GetActorUpVector() * GRID_SIZE / 2 + FVector::OneVector * GRID_SIZE/2);
	FIntVector Min = (FIntVector)GetComponentTransform().InverseTransformPosition(Panel.GetActorLocation() - Panel.GetActorUpVector() * GRID_SIZE / 2 - FVector::OneVector * GRID_SIZE / 2);

	Round(A, GRID_SIZE/2);
	Round(B, GRID_SIZE / 2);
	Round(Max, GRID_SIZE / 2);
	Round(Min, GRID_SIZE / 2);

	if (BBox.Min.X > Min.X) BBox.Min.X = Min.X;
	if (BBox.Min.Y > Min.Y) BBox.Min.Y = Min.Y;
	if (BBox.Min.Z > Min.Z) BBox.Min.Z = Min.Z;
	if (BBox.Max.X < Max.X) BBox.Max.X = Max.X;
	if (BBox.Max.Y < Max.Y) BBox.Max.Y = Max.Y;
	if (BBox.Max.Z < Max.Z) BBox.Max.Z = Max.Z;

	USpaceChunk* SCA=NULL, *SCB=NULL;
	if (!ChunksLocationMap.Contains(A)) {
		USpaceChunk* C = NewObject<USpaceChunk>(this);
		C->Initialize(A);
		SCA = C;
		C->SetupAttachment(this);
		C->RegisterComponent();
		ChunksLocationMap.Add(A, SCA);
		Chunks.Add(SCA);
	} else SCA = ChunksLocationMap[A];
	
	if (!ChunksLocationMap.Contains(B)) {
		USpaceChunk* C = NewObject<USpaceChunk>(this);
		C->Initialize(B);
		SCB = C;
		C->SetupAttachment(this);
		C->RegisterComponent();
		ChunksLocationMap.Add(B, SCB);
		Chunks.Add(SCB);
	} else SCB = ChunksLocationMap[B];

	Panel.RegisterSpaceChunks(SCA, SCB);

	for (int i = 0; i < 6; i++) {
		FIntVector QueryLocationA = A + (FIntVector)USpaceChunk::IndexToRelativeLocation(i) * GRID_SIZE;
		FIntVector QueryLocationB = B + (FIntVector)USpaceChunk::IndexToRelativeLocation(i) * GRID_SIZE;
		if (ChunksLocationMap.Contains(QueryLocationA)) {
			SCA->Neighbors[i] = ChunksLocationMap[QueryLocationA];
			int Idx = USpaceChunk::RelativeLocationToIndex(-USpaceChunk::IndexToRelativeLocation(i));
			ChunksLocationMap[QueryLocationA]->Neighbors[Idx] = SCA;
		}
		if (ChunksLocationMap.Contains(QueryLocationB)) {
			SCB->Neighbors[i] = ChunksLocationMap[QueryLocationB];
			int Idx = USpaceChunk::RelativeLocationToIndex(-USpaceChunk::IndexToRelativeLocation(i));
			ChunksLocationMap[QueryLocationB]->Neighbors[Idx] = SCB;
		}
	}

}




void USpaceEnclosure::Round(FIntVector& Vector, int Multiple) {
	RoundInt(Vector.X, Multiple);
	RoundInt(Vector.Y, Multiple);
	RoundInt(Vector.Z, Multiple);
}

void USpaceEnclosure::RoundInt(int& Integer, int Multiple) {
	int Sign = Integer >= 0 ? 1:-1;
	Integer = ((Integer + Sign * (Multiple - 1)) / Multiple) * Multiple;
}


