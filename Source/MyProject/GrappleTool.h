// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SplineComponent.h"

#include "GrappleTool.generated.h"

UCLASS()
class MYPROJECT_API AGrappleTool : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGrappleTool();
	UPROPERTY(EditDefaultsOnly)
	class USceneComponent* Root;
	UPROPERTY(EditAnywhere)
	class USplineComponent* Spline;
	UPROPERTY(EditDefaultsOnly)
	TArray<class USplineMeshComponent*> SplineMeshes;
	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* GrappleMesh;
	UPROPERTY(EditDefaultsOnly)
	USkeletalMesh* GrappleSkeletalMesh;
	UPROPERTY(EditAnywhere)
	//class USplineMeshComponent* SplineMesh;
	struct FSplinePoint StartPoint;
	struct FSplinePoint TargetPoint;
	float Key;
	float MaxLength;
	float UnitLength;
	UPROPERTY(EditDefaultsOnly)
	UStaticMesh* Mesh;
	FCollisionQueryParams CollisionParams;

	UFUNCTION(BlueprintCallable)
	void SetSplineMesh();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void AddCollisionIgnore(AActor* Actor);

};
