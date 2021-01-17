// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Globals.h"
#include "Components/SceneComponent.h"
#include "SpaceChunk.h"
#include "SpaceEnclosure.generated.h"

class APanel;
class USpaceChunk;
struct FSpaceChunkSet;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT_API USpaceEnclosure : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USpaceEnclosure();

	UPROPERTY(visibleAnywhere)
	TMap<FIntVector, USpaceChunk*> ChunksLocationMap;
	UPROPERTY(EditAnywhere)
	TArray<USpaceChunk*> Chunks;

	UPROPERTY(VisibleAnywhere)
	FBox BBox;

	TArray<FSpaceChunkSet> Subenclosures;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void CalculateSubenclosures();

public:	


	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void Initialize(FTransform InTransform, FVector InMinCorner, FVector InMaxCorner);

	void Expand(APanel& Panel);
	void Round(FIntVector& Vector, int Multiple);
	void RoundInt(int& Integer, int Multiple);
};
