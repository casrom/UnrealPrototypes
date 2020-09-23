// Fill out your copyright notice in the Description page of Project Settings.


#include "Attachment.h"
#include "../Globals.h"
#include "../PanelSide.h"

// Sets default values
AAttachment::AAttachment()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BuildItemInfo.CollisionChannel = COLLISION_CONNECTOR_ATTACH;
}

// Called when the game starts or when spawned
void AAttachment::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAttachment::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAttachment::OnBuild(ABuildItem* Parent) {
	Super::OnBuild(Parent);
	AttachmentParent = Parent;
	if (Parent != nullptr) AttachToActor(Parent, FAttachmentTransformRules::KeepWorldTransform);

}

UPanelSide* AAttachment::FindPanelSide() {
    UPanelSide* ResultPanelSide = nullptr;
    FHitResult Hit;
    FVector StartLocation = GetActorLocation();
    FVector EndLocation = StartLocation - (GetActorUpVector() * PANEL_THICKNESS / 2);
    //DrawDebugDirectionalArrow(GetWorld(), StartLocation, EndLocation, 10, FColor::Red, true, -1, 10, 3);

    if (GetWorld()->LineTraceSingleByChannel(Hit, StartLocation, EndLocation, COLLISION_PANELSIDE)) {
        if (Hit.GetComponent()->GetAttachParent() != nullptr) {
            UPanelSide* PanelSide = Cast<UPanelSide>(Hit.GetComponent()->GetAttachParent());
            //APanel* HitPanel = Cast<APanel>(Hit.GetActor());
            if (PanelSide != nullptr) {
                ResultPanelSide = PanelSide;
                DEBUGMESSAGE("FindPanelSide success\n");
                //}
            }
        }
    }
    return ResultPanelSide;
}

