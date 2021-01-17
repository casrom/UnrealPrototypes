// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BuildItem.h"

#include "Panel.generated.h"

class USpaceChunk;
class UPanelButton;
class UPanelSide;
class APowerColumn;
class UEnergyStrip;
class ABuilding;
class UBoxComponent;
class UConnectorComponent;

UCLASS()
class MYPROJECT_API APanel : public ABuildItem
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APanel();
	UPROPERTY(VisibleAnywhere)
	TArray<UConnectorComponent*> ConnectionColliders;
	
	UPROPERTY(editAnywhere, BlueprintReadWrite)
	bool bIsWall = false;

	UPROPERTY(editAnywhere, BlueprintReadWrite)
	float FlowEfficiency = 0;


	UPROPERTY(EditDefaultsOnly)
	TArray<class UConnectorComponent*> AttachmentColliders;



	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<APowerColumn> PowerCoreBP;
	UPROPERTY(VisibleAnywhere)
	APowerColumn* PowerCore;


	////UPROPERTY(visibleAnywhere)
	//class UBoxComponent* SideColliderA;
	////UPROPERTY(visibleAnywhere)
	//class UBoxComponent* SideColliderB;

	//class USpaceChunk* SpaceChunkA;
	//class USpaceChunk* SpaceChunkB;

	//UPROPERTY(visibleAnywhere)
	//TArray<class UBoxComponent*> SideColliders;
	//UPROPERTY(EditDefaultsOnly)
	//TArray<UPanelButton*> PanelButtons;
	//UPROPERTY(EditDefaultsOnly)
	//TArray<bool> PanelButtonIsVisible;

	//UPROPERTY(VisibleAnywhere)
	//TArray<UEnergyStrip*> PowerStrips;
	//UPROPERTY(EditAnywhere)
	//TSubclassOf<UEnergyStrip> EnergyStripBP;
	//UPROPERTY(EditDefaultsOnly)
	//bool bHasEnergyStrips = true;

	UFUNCTION(BlueprintCallable)
	void Init();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector Size;
	float Margin;

	UPROPERTY()
	TArray<UPanelSide*> Sides;

	UPROPERTY()
	ABuilding* Building;
	//TMap<int, struct FPanelSet&> ConnectedPanels;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FTransform IndexToTransform(int index);
	ECollisionChannel IndexToCollisionChannel(int index);


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void OnBuild(ABuildItem* Parent) override;

	void EnableConnectorTriggers();
	void DisableConnectorTriggers();
	static int ConnectorLocationToIndex(FVector Location);
	static FVector IndexToConnectorLocation(int index);
	FVector IndexToAttachmentLocation(int Index);

	//int PanelSideColliderToIndex(UBoxComponent* Collider);
	void Sweep(int EdgeIndex, int SideIndex);
	void SweepAll();
	FVector FindSweepDelta(int EdgeIndex, int SideIndex, FVector EdgeDirection);

	void RegisterSpaceChunks(USpaceChunk* SCA, USpaceChunk* SCB);
	void UpdateFlowEfficiency(float NewFlowEfficiency);
	//void InitializeEnclosure(USpaceEnclosure *Enclosure_);
	//void InitializeEnclosure();

};
