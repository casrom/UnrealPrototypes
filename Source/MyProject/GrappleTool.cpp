// Fill out your copyright notice in the Description page of Project Settings.


#include "GrappleTool.h"
#include "Components/SplineMeshComponent.h"
#include "Components/SplineComponent.h"
#include "DrawDebugHelpers.h"
#include "Macros.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AGrappleTool::AGrappleTool()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;
	Root->SetMobility(EComponentMobility::Movable);

	CollisionParams = FCollisionQueryParams();
	MaxLength = 1000;
	UnitLength = 50;
	for (int i = 0; i < 10; i++) {
		USplineMeshComponent* SplineMesh = CreateDefaultSubobject<USplineMeshComponent>(MakeUniqueObjectName(this, USplineMeshComponent::StaticClass(), "SplineMesh"));
		SplineMesh->SetupAttachment(Root);
		SplineMesh->SetRelativeLocation(FVector::ZeroVector);
		SplineMesh->SetMobility(EComponentMobility::Movable);
		SplineMeshes.Add(SplineMesh);
	}

	Spline = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
	Spline->SetupAttachment(Root);
	Spline->SetRelativeLocation(FVector::ZeroVector);
	Spline->SetMobility(EComponentMobility::Movable);

	GrappleMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Grapple"));
	GrappleMesh->SetupAttachment(Root);
	//GrappleMesh->SetRelativeRotation(FRotator(-90, 0, 0));
}

void AGrappleTool::SetSplineMesh() {
	for (auto SMesh : SplineMeshes) {
		SMesh->SetStaticMesh(Mesh);
	}
	GrappleMesh->SetSkeletalMesh(GrappleSkeletalMesh);
}

// Called when the game starts or when spawned
void AGrappleTool::BeginPlay()
{
	Super::BeginPlay();
	



}

// Called every frame
void AGrappleTool::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Key = FMath::Abs(FMath::Sin(GetGameTimeSinceCreation()));

	DrawDebugDirectionalArrow(GetWorld(), GetActorTransform().InverseTransformPosition(GetActorLocation()), GetActorForwardVector() * 100, 10, FColor::Red);
	
	StartPoint = FSplinePoint(0.0f, GetActorTransform().InverseTransformPosition(GetActorLocation()), GetActorRotation().GetInverse().RotateVector(GetActorForwardVector() * 10), GetActorRotation().GetInverse().RotateVector(-GetActorForwardVector()));

	FHitResult Hit;
	if (GetWorld()->LineTraceSingleByChannel(Hit, GetActorLocation(), GetActorLocation() + GetActorForwardVector() * 800, ECollisionChannel::ECC_WorldStatic, CollisionParams)) {

		StartPoint.LeaveTangent *= -Hit.Distance;
		TargetPoint = FSplinePoint(1, GetActorTransform().InverseTransformPosition(Hit.Location), GetActorRotation().GetInverse().RotateVector(-Hit.Normal * Hit.Distance), GetActorRotation().GetInverse().RotateVector(Hit.Normal * Hit.Distance));

		Spline->ClearSplinePoints();
		Spline->AddPoint(StartPoint);
		Spline->AddPoint(TargetPoint);

		for (auto SMesh : SplineMeshes) {
			SMesh->SetVisibility(false);
		}
		float SplineLength = Spline->GetSplineLength();
		float DisplayLength = SplineLength * Key;
		float CurrentEndDistance = DisplayLength;
		int SplineMeshIndex = 0;
		int NumSegments = SplineLength / UnitLength;
		FVector GrappleEndPos = Spline->GetLocationAtDistanceAlongSpline(CurrentEndDistance, ESplineCoordinateSpace::Local);
		FVector GrappleEndTan = Spline->GetTangentAtDistanceAlongSpline(CurrentEndDistance, ESplineCoordinateSpace::Local);
		GrappleMesh->SetRelativeLocation(GrappleEndPos);
		GrappleMesh->SetRelativeRotation(UKismetMathLibrary::MakeRotFromZX(GrappleEndTan, -FVector::UpVector));
		while (SplineMeshIndex < SplineMeshes.Num() && CurrentEndDistance > 0) {
			USplineMeshComponent* SplineMesh = SplineMeshes[SplineMeshIndex];
			SplineMesh->SetVisibility(true);
			float CurrentBeginDistance = CurrentEndDistance - UnitLength;
			FVector BeginPos = Spline->GetLocationAtDistanceAlongSpline(CurrentBeginDistance, ESplineCoordinateSpace::Local);
			FVector BeginTan = Spline->GetTangentAtDistanceAlongSpline(CurrentBeginDistance, ESplineCoordinateSpace::Local)/15;
			FVector EndPos = Spline->GetLocationAtDistanceAlongSpline(CurrentEndDistance, ESplineCoordinateSpace::Local);
			FVector EndTan = Spline->GetTangentAtDistanceAlongSpline(CurrentEndDistance, ESplineCoordinateSpace::Local)/ (15 + SplineMeshIndex);
			SplineMesh->SetStartAndEnd(BeginPos, BeginTan, EndPos, EndTan);
			SplineMeshIndex++;
			CurrentEndDistance = CurrentBeginDistance;
			//DrawDebugPoint(GetWorld(),GetActorTransform().TransformPosition(EndPos), 30, FColor::Red, false, -1, 12);
			//DrawDebugDirectionalArrow(GetWorld(), GetActorTransform().TransformPosition(EndPos), GetActorTransform().TransformPosition(EndPos + EndTan), 20, FColor::Red, false, -1, 12,2);
			//DrawDebugDirectionalArrow(GetWorld(), GetActorTransform().TransformPosition(BeginPos), GetActorTransform().TransformPosition(BeginPos + BeginTan), 20, FColor::Green, false, -1, 12, 2);
			//DrawDebugPoint(GetWorld(), GetActorTransform().TransformPosition(BeginPos), 20, FColor::Green, false, -1, 12);

		}

		//Spline->Gettlocation
		//FVector EndPos = Spline->GetLocationAtSplineInputKey(Key, ESplineCoordinateSpace::Local);
		//FVector EndTan = Spline->GetTangentAtSplineInputKey(Key, ESplineCoordinateSpace::Local);


	}

}


void AGrappleTool::AddCollisionIgnore(AActor* Actor) {
	CollisionParams.AddIgnoredActor(Actor);
}
