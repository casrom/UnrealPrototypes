// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"

#include "SpaceChunk.generated.h"

USTRUCT()
struct FSpaceChunkSet {
	GENERATED_BODY()

		TSet<USpaceChunk*> SpaceChunks;
	FSpaceChunkSet() {}
};

USTRUCT()
struct FSpaceChunkData {
	GENERATED_BODY()
	float Pressure;
	FColor Color;
	FSpaceChunkData() {}
};



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT_API USpaceChunk : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USpaceChunk();

	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* Collider;
	UPROPERTY(EditAnywhere)
	FSpaceChunkData Data;
	
	TArray<USpaceChunk*> Neighbors;
	TArray<float> FlowEfficiencies;

	FIntVector Center;

	float MaxFlowRate = 10;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Initialize(FIntVector InRelativeLocation);

	void FindConnectedChunks(TSet<USpaceChunk*>& OutChunks);
	static FVector IndexToRelativeLocation(int Index);
	static int RelativeLocationToIndex(FVector Location);
};
