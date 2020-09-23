// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"

#include "Globals.h"
#include "GameplayTagContainer.h"
#include "BuildItem.generated.h"

class UConnectorComponent;

USTRUCT(BlueprintType)
struct FBuildItemInfo {
	GENERATED_BODY()
	FBuildItemInfo()
	: bBuildableAnywhere(0)
	, CollisionChannel(0)
	{}

	UPROPERTY(EditAnywhere)
	bool bBuildableAnywhere;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag BuildItemTag;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRotator DefaultRotator = FRotator::ZeroRotator;
	UPROPERTY(visibleAnywhere)
	TEnumAsByte<ECollisionChannel> CollisionChannel;


};

UCLASS()
class MYPROJECT_API ABuildItem : public AActor
{
	GENERATED_BODY()


public:	
	// Sets default values for this actor's properties
	ABuildItem();


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class USceneComponent* Root;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UStaticMeshComponent* StaticVisualMesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class USkeletalMeshComponent* SkeletalVisualMesh;

	UPROPERTY(Instanced, EditDefaultsOnly)
	UBoxComponent* OverlapCollider;

	bool bOverlap = false;
	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


	UConnectorComponent* InUseConnector;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FBuildItemInfo BuildItemInfo;

	bool bReady = false;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void OnBuild(ABuildItem* Parent);

	static ABuildItem* SpawnBuildItemDisplay(UWorld* InWorld, TSubclassOf<ABuildItem> BuildItemBP);
};
