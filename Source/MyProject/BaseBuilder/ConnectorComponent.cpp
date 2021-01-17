// Fill out your copyright notice in the Description page of Project Settings.


#include "ConnectorComponent.h"
#include "Panel.h"
#include "Components/BoxComponent.h"
#include "../Macros.h"

UConnectorComponent::UConnectorComponent()
{

	PrimaryComponentTick.bCanEverTick = false;

	ConnectorCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	ConnectorCollider->SetupAttachment(this);

}

void UConnectorComponent::Init(FVector Size, APanel* Parent, ECollisionChannel InCollisionChannel, int Reduction, bool RegisterComponent) {
	//DEBUGMESSAGE("%x", InCollisionChannel);
	CollisionChannel = InCollisionChannel;
	Size = Size / 2;
	Size.X -= Reduction;
	ConnectorCollider->InitBoxExtent(Size);
	ConnectorCollider->SetRelativeLocation(FVector(-Reduction, 0, 0));
	ParentPanel = Parent;
	ConnectorCollider->SetCollisionProfileName("NoCollision");
	ConnectorCollider->SetCollisionResponseToChannel(CollisionChannel, ECollisionResponse::ECR_Block);
}


void UConnectorComponent::BeginPlay()
{
	Super::BeginPlay();
	ConnectorCollider->SetCollisionResponseToChannel(CollisionChannel, ECollisionResponse::ECR_Block);

}


void UConnectorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UConnectorComponent::Enable() {
	if (ConnectorCollider) {
		ConnectorCollider->SetCollisionProfileName("Trigger");
		ConnectorCollider->SetCollisionResponseToChannel(CollisionChannel, ECollisionResponse::ECR_Block);
		ConnectorCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}
}

void UConnectorComponent::Disable() {
	if (ConnectorCollider != NULL) ConnectorCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

