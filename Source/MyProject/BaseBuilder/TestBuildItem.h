// Copyright 2020 Siyi Cao. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TestBuildItem.generated.h"

UCLASS()
class MYPROJECT_API ATestBuildItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATestBuildItem();
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditDefaultsOnly)
	class UBoxComponent* OverlapCollider;

	//UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	//class USceneComponent* Root;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
