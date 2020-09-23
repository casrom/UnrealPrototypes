// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpaceEnclosure.h"
#include "Building.generated.h"

class APanel;
class UPanelSide;

USTRUCT(BlueprintType)
struct FSpaceSubenclosure {
	GENERATED_BODY()
	FSpaceSubenclosure() {}

	TSet<UPanelSide*> PanelSides;
	TSet<APanel*> Panels;
};

UCLASS()
class UPowerNetwork: public UObject {
	GENERATED_BODY()
public:
	UPowerNetwork() {};
	TSet<UPanelSide*> PanelSides;
	float Power = 0;
};

UCLASS()
class MYPROJECT_API ABuilding : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABuilding();

	USpaceEnclosure* Enclosure;

	TSet<APanel*> Panels;
	TSet<UPanelSide*> PanelSides;
	TSet<FSpaceSubenclosure*> Subenclosures;
	TArray<UPowerNetwork*> PowerNetworks;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void AddPanel(APanel& Panel);

	void FindPowerNetworks();

};
