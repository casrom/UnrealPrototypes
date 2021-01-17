// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildItem.h"
#include "Engine/SCS_Node.h"
#include "Globals.h"
#include "Components/BoxComponent.h"

ABuildItem::ABuildItem()
{
	PrimaryActorTick.bCanEverTick = false;
	
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;
	//StaticVisualMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticVisualMesh"));
	//SkeletalVisualMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalVisualMesh"));

	OverlapCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapTrigger"));
	OverlapCollider->SetCollisionProfileName("BuildOverlap");
	OverlapCollider->SetupAttachment(RootComponent);
	OverlapCollider->OnComponentBeginOverlap.AddDynamic(this, &ABuildItem::OnOverlapBegin);
	OverlapCollider->OnComponentEndOverlap.AddDynamic(this, &ABuildItem::OnOverlapEnd);
	OverlapCollider->SetGenerateOverlapEvents(true);

}

// Called when the game starts or when spawned
void ABuildItem::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ABuildItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ABuildItem::OnBuild(ABuildItem* Parent) {
	//if (RootComponent != nullptr && RootComponent != OverlapCollider){
	//	OverlapCollider->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	//}
	bReady = true;
}

void ABuildItem::InitBuildBlueprint() {
	if (StaticVisualMesh) {
		StaticVisualMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	if (SkeletalVisualMesh) {
		SkeletalVisualMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	//OverlapCollider is enabled by default

}

ABuildItem* ABuildItem::SpawnBuildItemDisplay(UWorld* InWorld, TSubclassOf<ABuildItem> BuildItemBP) {
	// fail attempt so far..
	//https://answers.unrealengine.com/questions/558236/how-to-get-a-component-from-a-classdefaultobject.html

	UStaticMeshComponent* StaticMesh = NULL;
	USkeletalMeshComponent* SkeletalMesh = NULL;
	ABuildItem* DisplayItem = Cast<ABuildItem>(InWorld->SpawnActor(ABuildItem::StaticClass()));
	return DisplayItem;
	//ABuildItem* CDO = Cast<ABuildItem>(InWorld->SpawnActor(BuildItemBP));
	//DisplayItem->BuildItemInfo = CDO->BuildItemInfo;
	////DisplayItem->OverlapCollider->DestroyComponent();
	////DisplayItem->OverlapCollider = NewObject<UBoxComponent>(DisplayItem, "OverlapCollider", RF_NoFlags, CDO->OverlapCollider);
	////DisplayItem->OverlapCollider->SetBoxExtent(CDO->OverlapCollider->GetUnscaledBoxExtent());
	////DisplayItem->OverlapCollider->RegisterComponent();
	//if (CDO->StaticVisualMesh != nullptr) {
	//	DisplayItem->StaticVisualMesh = NewObject<UStaticMeshComponent>(DisplayItem);
	//	DisplayItem->StaticVisualMesh->SetStaticMesh(CDO->StaticVisualMesh->GetStaticMesh());
	//	DisplayItem->StaticVisualMesh->SetCollisionProfileName("NoCollision");
	//	DisplayItem->StaticVisualMesh->SetRelativeLocation(FVector::ZeroVector);
	//	DisplayItem->StaticVisualMesh->AttachToComponent(DisplayItem->Root, FAttachmentTransformRules::KeepRelativeTransform);
	//	//DisplayItem->SetRootComponent(DisplayItem->StaticVisualMesh);
	//	//DisplayItem->OverlapCollider->AttachToComponent(DisplayItem->StaticVisualMesh, FAttachmentTransformRules::KeepRelativeTransform);
	//	DisplayItem->StaticVisualMesh->RegisterComponent();
	//}
	//if (CDO->SkeletalVisualMesh != nullptr) {
	//	DisplayItem->SkeletalVisualMesh = NewObject<USkeletalMeshComponent>(DisplayItem);
	//	DisplayItem->SkeletalVisualMesh->SetSkeletalMesh(CDO->SkeletalVisualMesh->SkeletalMesh);
	//	DisplayItem->SkeletalVisualMesh->SetCollisionProfileName("NoCollision");
	//	DisplayItem->SkeletalVisualMesh->SetRelativeLocation(FVector::ZeroVector);
	//	DisplayItem->SkeletalVisualMesh->AttachToComponent(DisplayItem->Root, FAttachmentTransformRules::KeepRelativeTransform);
	//	//DisplayItem->SetRootComponent(DisplayItem->SkeletalVisualMesh);
	//	//DisplayItem->OverlapCollider->AttachToComponent(DisplayItem->SkeletalVisualMesh, FAttachmentTransformRules::KeepRelativeTransform);
	//	DisplayItem->SkeletalVisualMesh->RegisterComponent();
	//}
	//CDO->Destroy();
	//return DisplayItem;
}

void ABuildItem::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) {
	//DEBUGMESSAGE("F%s\n", *OtherComp->GetFName().ToString());

		//if (OtherComp->ComponentHasTag("OverlapCollider")) {
	bOverlap = false;
		//}
	
}

void ABuildItem::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	//DEBUGMESSAGE("T%s\n", *OtherComp->GetFName().ToString());
	//if (OtherComp->ComponentHasTag("OverlapCollider")) {
	bOverlap = true;
	//}
	
}