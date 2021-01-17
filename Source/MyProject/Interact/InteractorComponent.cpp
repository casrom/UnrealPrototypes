// Fill out your copyright notice in the Description page of Project Settings.
#include "InteractorComponent.h"
#include "InteractableInterface.h"
#include "../Macros.h"
#include "../BaseBuilder/Macros.h"
#include "Kismet/GameplayStatics.h"
#include "../MainPlayerController.h"
#include "../UI/MainUI.h"

// Sets default values for this component's properties
UInteractorComponent::UInteractorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInteractorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	MPC = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
}


// Called every frame
void UInteractorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Interactable = nullptr;
	InteractableObject = nullptr;
	MPC->MainUI->Description = FText();
	if (Camera == nullptr) return;
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FHitResult Hit;
	float RayLength = 1000;

	FVector StartLocation = Camera->GetComponentLocation();
	FVector EndLocation = StartLocation + (Camera->GetForwardVector() * RayLength);
	MPC->MainUI->DeactivateCrosshair();

	if (GetWorld()->LineTraceSingleByChannel(Hit, StartLocation, EndLocation, COLLISION_INTERACTABLE)) {
		Interactable = Cast<IInteractableInterface>(Hit.Actor);
		InteractableObject = Cast<UObject>(Hit.Actor.Get());
		TriggerObject = Cast<UObject>(Hit.Component.Get());
		if (Interactable == nullptr) {
			if (Hit.Component.Get() != nullptr) {
				Interactable = Cast<IInteractableInterface>(Hit.Component.Get()->GetAttachParent());
				InteractableObject = Cast<UObject>(Hit.Component.Get()->GetAttachParent());
			}
		}
		//DEBUGMESSAGE("HIT %s\n", *Hit.GetActor()->GetFName().ToString());
		MPC->MainUI->ActivateCrosshair();
		if (Interactable != nullptr) {
			//DEBUGMESSAGE("%s\n", *Interactable->GetDescription().ToString());
			if (MPC != nullptr) MPC->MainUI->Description = Interactable->GetDescription();
		}
	}
	// ...
}

void UInteractorComponent::Interact() {
	if (Interactable != nullptr && InteractableObject != nullptr && TriggerObject != nullptr) {
		MPC->MainUI->InteractCrosshair();
		Interactable->Execute_OnInteract(InteractableObject, TriggerObject, this);
		//DEBUGMESSAGE("INTERACT\n");
	}
}


void UInteractorComponent::SetCamera(UCameraComponent* InCamera) {
	Camera = InCamera;
}
