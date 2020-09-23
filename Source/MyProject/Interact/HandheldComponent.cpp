// Fill out your copyright notice in the Description page of Project Settings.


#include "HandheldComponent.h"
#include "../GrappleTool.h"
#include "Camera/CameraComponent.h"

// Sets default values for this component's properties
UHandheldComponent::UHandheldComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHandheldComponent::BeginPlay()
{
	Super::BeginPlay();

	if (ToolBP == nullptr) return;
	Tool = GetWorld()->SpawnActor<AGrappleTool>(ToolBP);
	//MPC = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	Camera = GetOwner()->FindComponentByClass<UCameraComponent>();
	if (Camera != nullptr) {
		Tool->AttachToComponent(Camera, FAttachmentTransformRules::KeepRelativeTransform);
	}
	Tool->SetActorRelativeLocation(FVector(105, 0, -10));
	Tool->AddCollisionIgnore(GetOwner());
}


// Called every frame
void UHandheldComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

