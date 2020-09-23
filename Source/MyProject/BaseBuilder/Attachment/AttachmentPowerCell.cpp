// Fill out your copyright notice in the Description page of Project Settings.


#include "AttachmentPowerCell.h"
#include "../Building.h"
#include "../PanelSide.h"
#include "DrawDebugHelpers.h"


AAttachmentPowerCell::AAttachmentPowerCell() {
    StaticVisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    StaticVisualMesh->SetupAttachment(RootComponent);
}

void AAttachmentPowerCell::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);

    if (OutputPanelSide != nullptr) {
        if (OutputPanelSide->PowerNetwork != nullptr) {
            //DEBUGMESSAGE("UpdatePower %f\n", OutputPanelSide->PowerNetwork->Power);
            if (OutputPanelSide->PowerNetwork->Power < 255)
                OutputPanelSide->PowerNetwork->Power += 1;
        }
    }
}

void AAttachmentPowerCell::OnBuild(ABuildItem* Parent) {
    Super::OnBuild(Parent);
    OutputPanelSide = FindPanelSide();

}

