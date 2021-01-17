// Fill out your copyright notice in the Description page of Project Settings.


#include "Panel.h"
#include "PanelButton.h"
#include "PanelSide.h"
#include "PowerColumn.h"
#include "EnergyStrip.h"
#include "Building.h"
#include "DrawDebugHelpers.h"
#include "GameplayTagsManager.h"


#include "ConnectorComponent.h"
#include "Components/BoxComponent.h"
#include "Globals.h"

// Sets default values
APanel::APanel()
{	
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Size = FVector(GRID_SIZE, GRID_SIZE, 10);
	Margin = Size.Z + 0.1;

	StaticVisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	StaticVisualMesh->SetCollisionProfileName("BlockAll");
	//RootComponent = StaticVisualMesh;
	StaticVisualMesh->SetupAttachment(RootComponent);

	//OverlapCollider->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
	OverlapCollider->InitBoxExtent(Size/2 - FVector(Margin, Margin, 0));
	for (int i = 0; i < 2; i++) {
		FString Name = "Side";
		Name.AppendInt(i);
		UPanelSide* Side = CreateDefaultSubobject<UPanelSide>(FName(Name));
		Side->SetupAttachment(RootComponent);
		Side->SetRelativeLocation(FVector(0.0f, 0.0f, (0.5f - i) * Margin / 2));
		Side->Panel = this;
		Sides.Add(Side);
	}

	for (int i = 0; i < 4; i++) {
		Sides[0]->Neighbors[i] = Sides[1];
		Sides[1]->Neighbors[i] = Sides[0];
	}


	for (int i = 0; i < 12; i++) {
		FString Name = "PanelConnector";
		Name.AppendInt(i);
		UConnectorComponent* C = CreateDefaultSubobject<UConnectorComponent>(FName(Name));
		C->SetupAttachment(RootComponent);
		C->SetRelativeTransform(IndexToTransform(i));
		ConnectionColliders.Add(C);
		//C->RegisterComponent();
	}

	for (int i = 0; i < 8; i++) {
		FString Name = "AttachmentConnector";
		Name.AppendInt(i);
		UConnectorComponent* C = CreateDefaultSubobject<UConnectorComponent>(FName(Name));
		C->SetupAttachment(RootComponent);
		C->Init(FVector(80,80,20), this, COLLISION_CONNECTOR_ATTACH, 0);
		FVector Location = IndexToAttachmentLocation((i / 2)) * GRID_SIZE / 4;
		FRotator Rotation = FRotator::ZeroRotator;
		if (i % 2 == 0) {
			Location.Z = PANEL_THICKNESS / 2;
		} else {
			Location.Z = -PANEL_THICKNESS / 2;
			Rotation = FRotator(180, 0, 0);
		}
		C->SetRelativeLocationAndRotation(Location, Rotation);
		C->ConnectorCollider->SetCollisionProfileName("BuildAttachment");
		C->GameplayTags.AddTag(UGameplayTagsManager::Get().RequestGameplayTag("BuildItem.Attachment.M"));
		AttachmentColliders.Add(C);
	}


	//static ConstructorHelpers::FObjectFinder<UStaticMesh> StripMesh(TEXT("/Game/Blender/Panel_PowerStrip"));


	//PanelButtonIsVisible.Init(false, 4);
	//PanelButtons.Init(nullptr, 8);
	//PowerStrips.Init(nullptr, 8);

	//Init();
}

// Called when the game starts or when spawned
void APanel::BeginPlay()
{
	Super::BeginPlay();

	if (StaticVisualMesh)
		StaticVisualMesh->GetBodySetup()->CollisionTraceFlag = ECollisionTraceFlag::CTF_UseComplexAsSimple;

	if (bIsWall) {
		BuildItemInfo.DefaultRotator = FRotator(90, 0, 0);
		BuildItemInfo.CollisionChannel = COLLISION_CONNECTOR_WALL;
	} else {
		BuildItemInfo.CollisionChannel = COLLISION_CONNECTOR_FLOOR;
		BuildItemInfo.bBuildableAnywhere = true;
	}

	for (int i = 0; i < 12; i++) {
		UConnectorComponent* C = ConnectionColliders[i];
		ECollisionChannel CC = IndexToCollisionChannel(i);
		if (CC == COLLISION_CONNECTOR_WALL || bIsWall) C->Init(Size, this, CC, GRID_SIZE - 300, true);
		else C->Init(Size, this, CC, 0, true);
	}
}

void APanel::Init() {

	//for (int i = 0; i < 12; i++) {
	//	UConnectorComponent* C = ConnectionColliders[i];
	//	ECollisionChannel CC = IndexToCollisionChannel(i);
	//	if (CC == COLLISION_CONNECTOR_WALL || bIsWall) C->Init(Size, this, CC, GRID_SIZE - 300, true);
	//	else C->Init(Size, this, CC, 0, true);
	//}

	//for (int i = 0; i < 8; i++) {
	//	bool Visible = PanelButtonIsVisible[i / 2];
	//	if (Visible) {
	//		UPanelButton* Button = NewObject<UPanelButton>(this, MakeUniqueObjectName(this, UPanelButton::StaticClass(), "PanelButton"));
	//		Button->SetupAttachment(RootComponent);

	//		Button->RegisterComponent();
	//		PanelButtons[i] = Button;
	//		FVector Location = IndexToConnectorLocation(i / 2) * GRID_SIZE/2;
	//		FRotator Rotator = FRotator::ZeroRotator;
	//		if (i % 2 == 0) Rotator.Pitch = 180;
	//		if ((i / 2) % 2 == 0) Rotator.Yaw = 90;
	//		Button->Init(Location, Rotator);
	//	}
	//}

	//for (int i = 0; i < 8; i++) {
	//	if (!bHasEnergyStrips || EnergyStripBP == nullptr || PowerStrips[7] != nullptr) break;
	//	UEnergyStrip* ES = NewObject<UEnergyStrip>(RootComponent, EnergyStripBP, MakeUniqueObjectName(this, UEnergyStrip::StaticClass(), "EnergyStrip"));
	//	FRotator Rotator = FRotator::ZeroRotator;
	//	if (i < 4) { //Up Side
	//		Rotator = FRotator(0, i * 90, 0);
	//		Sides[0]->EnergyStrips[i] = ES;
	//	} else { //Down Side
	//		if (i % 2 == 1) Rotator = FRotator(180, -(i - 4) * 90, 0);
	//		else Rotator = FRotator(180, (i - 4) * 90 + 180, 0);
	//		Sides[1]->EnergyStrips[i-4] = ES;
	//	}
	//	ES->SetupAttachment(RootComponent);
	//	ES->RegisterComponent();
	//	ES->Init(Rotator);
	//	PowerStrips[i] = ES;
	//}


}

// Called every frame
void APanel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//FVector v = GetActorUpVector();
	//FPlane plane = FPlane(GetActorTransform().TransformPosition(FVector(0, 0, Size.Z)), GetActorUpVector());
	//DrawDebugSolidPlane(GetWorld(), plane, GetActorLocation(),  FVector2D(Size.X, Size.Y), Sides[0].Color);
	//plane = FPlane(GetActorTransform().TransformPosition(FVector(0, 0, -Size.Z)), -GetActorUpVector());
	//DrawDebugBox(GetWorld(), GetActorTransform().TransformPosition(FVector(0, 0, -20)), FVector::OneVector * 2, Sides[1].Data.Color, false, -1, 10);
	//DrawDebugSolidPlane(GetWorld(), plane, GetActorLocation(), FVector2D(Size.X, Size.Y), Sides[1].Color);
	//DrawDebugDirectionalArrow(GetWorld(), GetActorLocation(), GetActorLocation() + GetActorUpVector() * 50, 50, FColor::Red);
	//DrawDebugDirectionalArrow(GetWorld(), GetActorLocation() + FVector::UpVector * 20, GetActorLocation() + GetActorForwardVector() * 50 + FVector::UpVector * 20, 50, FColor::Red);

	//Draw Side debug
	//for (int j = 0; j < 2; j++) {
	//	for (int i = 0; i < 4; i++) {
	//		FPanelSide* Neighbor = Sides[j].Neighbors[i];
	//		FVector Location = GetActorTransform().TransformPosition(IndexToConnectorLocation(i) *(Size.X - Margin) + FVector(0, 0, (0.5 - j) * Size.Z * 2));
	//		if (Neighbor != NULL) {
	//			DrawDebugBox(GetWorld(), Location, FVector(1, 1, 1), Neighbor->Data.Color);
	//			//DrawDebugDirectionalArrow(GetWorld(), Location, Neighbor->Collider->GetComponentLocation(), 10, Sides[j].Color);
	//		}
	//		else {
	//			DrawDebugBox(GetWorld(), Location, FVector(1, 1, 1), FColor::White);
	//		}
	//	}

}

/*
converts an index (0-3) to the relative location of the connection collider starts at north, then clockwise from 0 to 3
*/
FVector APanel::IndexToConnectorLocation(int index) {
	switch (index){
	case 0:
		return FVector(1, 0, 0);
	case 1:
		return FVector(0, 1, 0);
	case 2:
		return FVector(-1, 0, 0);
	case 3:
		return FVector(0, -1, 0);
	}
	return FVector(0, 0, 0);
}

FTransform APanel::IndexToTransform(int index) {
	switch (index) {
	case 0:
		return FTransform(FRotator(0, 0, 0), FVector(1, 0, 0) * GRID_SIZE);
	case 1:
		return FTransform(FRotator(0, 90, 0), FVector(0, 1, 0) * GRID_SIZE);
	case 2:
		return FTransform(FRotator(0, 180, 0), FVector(-1, 0, 0) * GRID_SIZE);
	case 3:
		return FTransform(FRotator(0, 270, 0), FVector(0, -1, 0) * GRID_SIZE);
	case 4:
		return FTransform(FRotator(90,0,180), FVector(.5, 0, .5) * GRID_SIZE );
	case 5:
		return FTransform(FRotator(90, 0, 270), FVector(0, .5, .5) * GRID_SIZE);
	case 6:
		return FTransform(FRotator(90, 0, 0), FVector(-.5, 0, .5) * GRID_SIZE);
	case 7:
		return FTransform(FRotator(90, 0, 90), FVector(0, -.5, .5) * GRID_SIZE);
	case 8:
		return FTransform(FRotator(-90, 0, 180), FVector(.5, 0, -.5) * GRID_SIZE);
	case 9:
		return FTransform(FRotator(-90, 0, 270), FVector(0, .5, -.5) * GRID_SIZE);
	case 10:
		return FTransform(FRotator(-90, 0, 0), FVector(-.5, 0, -.5) * GRID_SIZE);
	case 11:
		return FTransform(FRotator(-90, 0, 90), FVector(0, -.5, -.5) * GRID_SIZE);


	}
	return FTransform();
}

ECollisionChannel APanel::IndexToCollisionChannel(int index) {
	if (bIsWall) {
		if (index < 4) return COLLISION_CONNECTOR_WALL; //0 1 2 3
		if (index % 2 == 0) return COLLISION_CONNECTOR_FLOOR; //4 6 8 10
		return COLLISION_CONNECTOR_WALL; //5 7 9 11
	} else {
		if (index < 4) return COLLISION_CONNECTOR_FLOOR;
		return COLLISION_CONNECTOR_WALL;
	}
}

FVector APanel::IndexToAttachmentLocation(int Index) {
	switch (Index) {
	case 0: return FVector(1, 1, 0);
	case 1: return FVector(1, -1, 0);
	case 2: return FVector(-1, -1, 0);
	case 3: return FVector(-1, 1, 0);
	}
	return FVector();
}


void APanel::OnBuild(ABuildItem* Parent) {
	Super::OnBuild(Parent);
	//StaticVisualMesh->SetCollisionProfileName("BlockAll");
	//StaticVisualMesh->SetCollisionProfileName("BlockAll");
	EnableConnectorTriggers();

	PowerCore = (APowerColumn*)GetWorld()->SpawnActor(PowerCoreBP);
	if (PowerCore != nullptr) {
		PowerCore->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
		PowerCore->RegisterEnergyDiscs();
	}
}

int APanel::ConnectorLocationToIndex(FVector Location)
{	
	Location.Normalize();
	if (Location.Equals(FVector(1, 0, 0))) {
		return 0;
	} else if (Location.Equals(FVector(0, 1, 0),0.01)) {
		return 1;
	}  else if (Location.Equals(FVector(-1, 0, 0), 0.01)) {
		return 2;
	} else if (Location.Equals(FVector(0, -1, 0), 0.01)) {
		return 3;
	}
	return -1;
}

void APanel::Sweep(int EdgeIndex, int SideIndex)
{
	FHitResult Hit;
	float StepSize = Margin * 2;
	FVector EdgeDirection = IndexToConnectorLocation(EdgeIndex);
	FVector Current = EdgeDirection * (GRID_SIZE/2 - Margin);
	FCollisionShape CollisionShape = FCollisionShape::MakeBox(FVector::OneVector);
	//DEBUGMESSAGE("SWEEP[%d %d]\n", EdgeIndex, SideIndex);
	for (int i = 0; i < 5; i++) {
		FVector Next = Current + FindSweepDelta(i,SideIndex,EdgeDirection) * StepSize;
		//DrawDebugBox(GetWorld(), GetActorTransform().TransformPosition(Current), FVector(1, 1, 1), FColor::Red, true, -1, 10);
		//DrawDebugBox(GetWorld(), GetActorTransform().TransformPosition(Next), FVector(1, 1, 1), FColor::Blue, true, -1, 10);

		if (GetWorld()->SweepSingleByChannel(Hit, GetActorTransform().TransformPosition(Current), GetActorTransform().TransformPosition(Next), FQuat::Identity, COLLISION_PANELSIDE, CollisionShape)) {
			if (Hit.GetComponent()->GetAttachParent()!=nullptr) {
				//Found valid connection
				UPanelSide* HitPanelSide = Cast<UPanelSide>(Hit.GetComponent()->GetAttachParent());
				if (HitPanelSide != nullptr) {
					//UBoxComponent* SideCollider = Cast<UBoxComponent>(Hit.GetComponent());
					APanel* HitPanel = Cast<APanel>(Hit.GetActor());
					if (HitPanel != nullptr && HitPanel != this) {
						//int HitSideIndex = HitPanel->PanelSideColliderToIndex(SideCollider);
						FVector V = Hit.Location - HitPanelSide->GetComponentLocation();
						//V = HitPanel->GetTransform().InverseTransformPosition(V);
						V = FVector::VectorPlaneProject(V, HitPanelSide->GetUpVector());
						V.Normalize();
						V = HitPanel->GetActorRotation().GetInverse().RotateVector(V);
						int HitEdgeIndex = ConnectorLocationToIndex(V);
						//DEBUGMESSAGE("Panel[%d] S%d E%d <--> Panel[%d] S%d E%d\n",GetUniqueID(), SideIndex, EdgeIndex, HitPanel->GetUniqueID(), HitPanelSide->GetUniqueID(), HitEdgeIndex);
						if (HitEdgeIndex != -1) {
							UPanelSide* PanelSide = Sides[SideIndex];
							PanelSide->Neighbors[EdgeIndex] = HitPanelSide;
							PanelSide->RelativeSideIndices[EdgeIndex] = HitEdgeIndex;
							HitPanelSide->Neighbors[HitEdgeIndex] = PanelSide;
							HitPanelSide->RelativeSideIndices[HitEdgeIndex] = EdgeIndex;

							TSet<UPanelSide*> Set;
							FPanelSideData Data = FPanelSideData(FColor::MakeRandomColor());
							UPanelSide::PropagateData(Sides[SideIndex], Set, Data);
							break;
						}

					}
				}
			}
		}
		Current = Next;
	}
}

void APanel::SweepAll() {
	for (int i = 0; i < 4; i++) {
		Sweep(i, 0);
		Sweep(i, 1);
	}
}


FVector APanel::FindSweepDelta(int i, int SideIndex, FVector EdgeDirection) {
	int Sign = SideIndex == 0 ? 1 : -1;
	switch(i) {
	case 0: return FVector(0, 0, 1) * Sign;
	case 1: return EdgeDirection;
	case 2: return FVector(0, 0, -2) * Sign;
	case 3: return -EdgeDirection;
	case 4: return FVector(0, 0, 1) * Sign;
	}
	return FVector(0, 0, 0);
}



void APanel::EnableConnectorTriggers() {
	for (int i = 0; i < 12; i++) {
		ConnectionColliders[i]->Enable();
	}
}

void APanel::DisableConnectorTriggers() {
	for (int i = 0; i < 12; i++) {
		//ConnectionColliders[i]->Disable();
	}
}


void APanel::UpdateFlowEfficiency(float NewFlowEfficiency) {
	for (UPanelSide* Side : Sides) {
		if (Side->SpaceChunk != nullptr && Side->SideIndexOfChunk != -1) Side->SpaceChunk->FlowEfficiencies[Side->SideIndexOfChunk] = NewFlowEfficiency;
	}
}

void APanel::RegisterSpaceChunks(USpaceChunk* SCA, USpaceChunk* SCB) {
	if (!(Sides[0] && Sides[1])) {
		DEBUGMESSAGE("Error: Sides Nulled! unable to register space chunks");
		return;
	}
	Sides[1]->SpaceChunk = SCA;
	Sides[0]->SpaceChunk = SCB;


	FVector PanelRelativeLocationA = SCA->GetComponentTransform().InverseTransformPosition(GetActorLocation());
	PanelRelativeLocationA.Normalize();
	int PanelIndexA = USpaceChunk::RelativeLocationToIndex(PanelRelativeLocationA);
	if (PanelIndexA != -1) {
		SCA->FlowEfficiencies[PanelIndexA] = FlowEfficiency;
		Sides[1]->SideIndexOfChunk = PanelIndexA;
		//DEBUGMESSAGE("SetFLOWA = %d, %s\n", PanelIndexA, *PanelRelativeLocationA.ToString());
	}

	FVector PanelRelativeLocationB = SCB->GetComponentTransform().InverseTransformPosition(GetActorLocation());
	PanelRelativeLocationB.Normalize();
	int PanelIndexB = USpaceChunk::RelativeLocationToIndex(PanelRelativeLocationB);
	if (PanelIndexB != -1) {
		SCB->FlowEfficiencies[PanelIndexB] = FlowEfficiency;
		Sides[0]->SideIndexOfChunk = PanelIndexB;
		//DEBUGMESSAGE("SetFLOWB = %d, %s\n", PanelIndexB, *PanelRelativeLocationB.ToString());
	}
}

