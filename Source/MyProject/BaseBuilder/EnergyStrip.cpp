// Fill out your copyright notice in the Description page of Project Settings.


#include "EnergyStrip.h"
#include "Building.h" //PowerNetwork

// Sets default values for this component's properties
UEnergyStrip::UEnergyStrip()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...


	//StaticVisualMesh->SetupAttachment(this);

//	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMesh(TEXT("/Game/Blender/Panel_PowerStrip"));


}


// Called when the game starts
void UEnergyStrip::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UEnergyStrip::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (MaterialInstance != nullptr) {
		if (PowerNetwork != nullptr)
			MaterialInstance->SetVectorParameterValue("BaseColor", FColor(0, PowerNetwork->Power, 0));
		else
			MaterialInstance->SetVectorParameterValue("BaseColor", ColorDefault);
	}
}

void UEnergyStrip::Init(FRotator Rotator) {
	if (StaticMesh != nullptr ) {
		StaticVisualMesh = NewObject<UStaticMeshComponent>(this, TEXT("Mesh"));
		StaticVisualMesh->SetupAttachment(this);
		StaticVisualMesh->SetStaticMesh(StaticMesh);
		StaticVisualMesh->SetRelativeRotation(Rotator);
		StaticVisualMesh->SetRelativeLocation(FVector::ZeroVector);
		StaticVisualMesh->RegisterComponent();
		StaticVisualMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		MaterialInstance = StaticVisualMesh->CreateDynamicMaterialInstance(0);
		FHashedMaterialParameterInfo Info = FHashedMaterialParameterInfo("BaseColor");
		MaterialInstance->GetVectorParameterValue(Info, ColorDefault);
	}
}

void UEnergyStrip::ActivateEnergyStrip(UPowerNetwork* InPowerNetwork) {
	PowerNetwork = InPowerNetwork;
}

void UEnergyStrip::DeactivateEnergyStrip() {
	PowerNetwork = nullptr;
}