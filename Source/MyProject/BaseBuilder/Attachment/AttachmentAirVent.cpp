// Fill out your copyright notice in the Description page of Project Settings.


#include "AttachmentAirVent.h"
#include "../Globals.h"
#include "../PanelSide.h"
#include "../SpaceChunk.h"
#include "Components/BoxComponent.h"

#include "DrawDebugHelpers.h"

AAttachmentAirVent::AAttachmentAirVent() {
    StaticVisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    StaticVisualMesh->SetupAttachment(RootComponent);
}

void AAttachmentAirVent::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);

    if (OutputPanelSide != NULL) {
        OutputSpaceChunk = OutputPanelSide->SpaceChunk;
        if (OutputSpaceChunk->Data.Pressure < 1000)
            OutputSpaceChunk->Data.Pressure += 10;
        //TSet<FPanelSide*> Visited;
        //FPanelSideData Data = OutputPanelSide->Data;
        //Data.Color = FColor::Red;
        //APanel::PropagateSide(Output, Visited, Data);
    }


    DrawDebugBox(GetWorld(), GetActorLocation() + GetActorUpVector() * 20, FVector::OneVector, FColor::Blue, false, -1, 10);
    DrawDebugBox(GetWorld(), GetActorLocation(), FVector::OneVector, FColor::Blue, false, -1, 10);
    //if (OutputPanelSide != NULL) {
        //DrawDebugBox(GetWorld(), OutputPanelSide->Collider->GetComponentLocation(), FVector::OneVector, FColor::Blue, false, -1, 10);
    //}
}

void AAttachmentAirVent::OnBuild(ABuildItem* Parent) {
    Super::OnBuild(Parent);

    DEBUGMESSAGE("BuildVent\n");
    OutputPanelSide = FindPanelSide();


    //TEST
    if (OutputPanelSide != NULL) {
        OutputSpaceChunk = OutputPanelSide->SpaceChunk;
        OutputSpaceChunk->Data.Pressure = 100;
        //TSet<FPanelSide*> Visited;
        //FPanelSideData Data = OutputPanelSide->Data;
        //Data.Color = FColor::Red;
        //APanel::PropagateSide(Output, Visited, Data);
    }

}
