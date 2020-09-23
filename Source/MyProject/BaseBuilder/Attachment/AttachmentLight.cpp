// Fill out your copyright notice in the Description page of Project Settings.


#include "AttachmentLight.h"
#include "../Building.h"
#include "../PanelSide.h"

AAttachmentLight::AAttachmentLight() {
    StaticVisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    StaticVisualMesh->SetupAttachment(RootComponent);

    Light = CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight"));
    Light->SetupAttachment(RootComponent);
    Light->SetIntensity(0);
    MaxIntensity = 1000;
}

void AAttachmentLight::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);

    Brightness = 0;
    if (InputPanelSide != nullptr) {
        if (InputPanelSide->PowerNetwork != nullptr) {
            //DEBUGMESSAGE("UpdatePower %f\n", OutputPanelSide->PowerNetwork->Power);
            //if (InputPanelSide->PowerNetwork->Power < 255)
            //InputPanelSide->PowerNetwork->Power += 1;
            Brightness = InputPanelSide->PowerNetwork->Power / 255;
        }
    }

    Light->SetIntensity(Brightness * MaxIntensity);
}

void AAttachmentLight::OnBuild(ABuildItem* Parent) {
    Super::OnBuild(Parent);
    InputPanelSide = FindPanelSide();

}