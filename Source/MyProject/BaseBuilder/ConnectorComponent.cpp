// Fill out your copyright notice in the Description page of Project Settings.


#include "ConnectorComponent.h"
#include "Panel.h"
#include "Components/BoxComponent.h"

// Sets default values for this component's properties
UConnectorComponent::UConnectorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	ConnectorCollider = CreateDefaultSubobject<UBoxComponent>(MakeUniqueObjectName(this, UBoxComponent::StaticClass(), "ConnectorCollider"));
	//ConnectorCollider->SetCollisionProfileName("NoCollision");
	//ConnectorCollider->ComponentTags.Add(ConnectorTag.GetTagName());
	ConnectorCollider->SetupAttachment(this);
	//ConnectorCollider->SetRelativeLocation(FVector::ZeroVector);

}

void UConnectorComponent::Init(FVector Size, APanel* Parent, ECollisionChannel InCollisionChannel, int Reduction, bool RegisterComponent) {
	//ConnectorCollider = NewObject<UBoxComponent>(this);
	//ConnectorCollider->AttachToComponent(this, FAttachmentTransformRules::KeepRelativeTransform);
	CollisionChannel = InCollisionChannel;
	Size = Size / 2;
	Size.X -= Reduction;
	ConnectorCollider->InitBoxExtent(Size);
	ConnectorCollider->SetRelativeLocation(FVector(-Reduction, 0, 0));
	ParentPanel = Parent;
	ConnectorCollider->SetCollisionProfileName("NoCollision");
	ConnectorCollider->SetCollisionResponseToChannel(CollisionChannel, ECollisionResponse::ECR_Block);
	//if (RegisterComponent)
		//ConnectorCollider->RegisterComponent();
}


// Called when the game starts
void UConnectorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UConnectorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	

	// ...
}

void UConnectorComponent::Enable() {
	if (ConnectorCollider != NULL) {
		ConnectorCollider->SetCollisionProfileName("Trigger");
		ConnectorCollider->SetCollisionResponseToChannel(CollisionChannel, ECollisionResponse::ECR_Block);
		ConnectorCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}
}

void UConnectorComponent::Disable() {
	if (ConnectorCollider != NULL) ConnectorCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

//void UConnectorComponent::MergeTo(UConnectorComponent* Connector)
//{
//	//Connector->Parents.Append(Parents);
//	//Connector->Parents.Empty();
//	Disable();
//}
//
//void UConnectorComponent::AddConnectedPanel(int EdgeIndex, APanel* Panel)
//{
//	check(EdgeIndex >= 0 && EdgeIndex < 4);
//	check(!ConnectedPanels[EdgeIndex].Panels.Contains(Panel));
//	EdgeIndex = (EdgeIndex + 2) % 4;
//	ConnectedPanels[EdgeIndex].Panels.Add(Panel);
//}
//
//void UConnectorComponent::Connect(APanel* Panel)
//{
//	Panel->ConnectedPanels = ConnectedPanels;
//	for (int i = 0; i < 4; i++) {
//		for (APanel* P : ConnectedPanels[i].Panels) {
//			int j = (i + 2) % 4;
//			P->ConnectPanel(j, Panel);
//		}
//	}
//	Disable();
//}
