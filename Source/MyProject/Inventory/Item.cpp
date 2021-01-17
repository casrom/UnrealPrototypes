// Fill out your copyright notice in the Description page of Project Settings.
#include "Item.h"
#include "Components/BoxComponent.h"
#include "../Interact/InteractorComponent.h"
#include "InventoryComponent.h"
#include "../Macros.h"


AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = false;
	Info = FItemInfo();
	/*if (Info.StaticVisualMesh) {
		VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Visual Mesh"));
		VisualMesh->SetStaticMesh(Info.StaticVisualMesh);
	}*/
	VisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualMesh"));
	RootComponent = VisualMesh;
	InteractTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractTrigger"));
	InteractTrigger->SetCollisionProfileName("InteractTrigger");
	InteractTrigger->SetupAttachment(VisualMesh);

}

void AItem::BeginPlay()
{

	Super::BeginPlay();
	Info.ItemBP = this->GetClass();
	InteractTrigger->SetRelativeLocation(FVector::ZeroVector);

}

void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItem::OnInteract_Implementation(UObject* TriggeredObject, UObject* Interactor) {
	UInteractorComponent* InteractorC = Cast<UInteractorComponent>(Interactor);
	UInventoryComponent* Inventory = nullptr;
	if (InteractorC) {
		Inventory = Cast<UInventoryComponent>(InteractorC->GetOwner()->GetComponentByClass(UInventoryComponent::StaticClass()));
	}
	if (Inventory) {
		//DEBUGMESSAGE("%x", Inventory);
		Inventory->AddItem(Info);
		Destroy();
	}
}

FText AItem::GetDescription() {
	return FText::Format(NSLOCTEXT("DefaultNamespace", "PickUp", "{0} \n Pick Up (E)"), Info.Name);
}

