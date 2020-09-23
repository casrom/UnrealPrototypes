// Fill out your copyright notice in the Description page of Project Settings.


#include "AttachmentDoor.h"
#include "Animation/AnimInstance.h"
#include "../../Macros.h"
#include "../Panel.h"

AAttachmentDoor::AAttachmentDoor() {

    SkeletalVisualMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
    SkeletalVisualMesh->SetCollisionProfileName("BlockAll");
    SkeletalVisualMesh->SetupAttachment(RootComponent);
}

void AAttachmentDoor::OnBuild(ABuildItem* Parent) {
    Super::OnBuild(Parent);

    

    if (InteractTrigger != nullptr) {
        InteractTrigger->SetCollisionProfileName("InteractTrigger");
    }

    ParentPanel = Cast<APanel>(AttachmentParent);
    if (ParentPanel != nullptr) ParentPanel->UpdateFlowEfficiency(0);
    //UAnimInstance* AnimInstance = SkeletalVisualMesh->GetAnimInstance();
}

void AAttachmentDoor::OnInteract_Implementation(UObject* TriggeredObject) {
    //DEBUGMESSAGE("Interact %x\n", bOpen);
    if (ParentPanel != nullptr) {
        if (bOpen) ParentPanel->UpdateFlowEfficiency(0);
        else ParentPanel->UpdateFlowEfficiency(1);
    }
    bOpen = !bOpen;
}

FText AAttachmentDoor::GetDescription() {
    if (bOpen) {
        return FText::FromString("Close (E)");
    } else {
        return FText::FromString("Open (E)");
    }
}