// Copyright 2020 Siyi Cao. All Rights Reserved.


#include "TestBuildItem.h"
#include "Components/BoxComponent.h"

// Sets default values
ATestBuildItem::ATestBuildItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("STATICMESH"));
	RootComponent = StaticMesh;

	OverlapCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Overlap"));
	OverlapCollider->SetCollisionProfileName("BuildOverlap");
	//OverlapCollider->OnComponentBeginOverlap.AddDynamic(this, &ABuildItem::OnOverlapBegin);
	//OverlapCollider->OnComponentEndOverlap.AddDynamic(this, &ABuildItem::OnOverlapEnd);
	OverlapCollider->SetGenerateOverlapEvents(true);
}

// Called when the game starts or when spawned
void ATestBuildItem::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATestBuildItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

