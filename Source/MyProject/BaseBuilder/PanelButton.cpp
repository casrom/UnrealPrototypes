// Fill out your copyright notice in the Description page of Project Settings.


#include "PanelButton.h"
#include "Components/BoxComponent.h"

UPanelButton::UPanelButton()
{
	PrimaryComponentTick.bCanEverTick = false;
	SkeletalVisualMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	SkeletalVisualMesh->SetupAttachment(this);
	SkeletalVisualMesh->SetCollisionProfileName("BlockAll");
	InteractCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Interact Collider"));
	InteractCollider->SetupAttachment(this);
	SkeletalVisualMesh->SetCollisionProfileName("InteractTrigger");

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SkeletalMesh(TEXT("/Game/Blender/Panel_Button"));
	if (SkeletalMesh.Succeeded()) {
		SkeletalVisualMesh->SetSkeletalMesh(SkeletalMesh.Object);
	}

	static ConstructorHelpers::FObjectFinder<UAnimationAsset> Animation(TEXT("/Game/Blender/Animations/Press"));
	if (Animation.Succeeded()) {
		PressAnimation = Animation.Object;

	}
	InteractCollider->SetBoxExtent(FVector(20, 10, 10));
	InteractCollider->SetRelativeLocation(FVector(0, 0, 20));

	MaterialInstance = SkeletalVisualMesh->CreateDynamicMaterialInstance(1);
	if (MaterialInstance!=nullptr)
		MaterialInstance->SetVectorParameterValue("BaseColor", FColor::White);

}


// Called when the game starts
void UPanelButton::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UPanelButton::Init(FVector InRelativeLocation, FRotator InRelativeRotator) {
	SetRelativeLocation(InRelativeLocation);
	SetRelativeRotation(InRelativeRotator);
	SkeletalVisualMesh->RegisterComponent();
	InteractCollider->RegisterComponent();
}


// Called every frame
void UPanelButton::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void UPanelButton::OnInteract_Implementation(UObject* TriggeredObject, UObject* Interactor) {
	if (PressAnimation != nullptr){
		if (!SkeletalVisualMesh->IsPlaying()) {
			bActive = !bActive;
			SkeletalVisualMesh->PlayAnimation(PressAnimation, false);
		}
	}

	if (MaterialInstance != NULL) {
		if (bActive) {
			MaterialInstance->SetVectorParameterValue("BaseColor", FColor::Green);
		} else {
			MaterialInstance->SetVectorParameterValue("BaseColor", FColor::White);
		}
	}

}

FText UPanelButton::GetDescription() {
	return FText::FromString("Connect (E)");
}