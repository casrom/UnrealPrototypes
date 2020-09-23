// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "EnergyStrip.generated.h"


UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT_API UEnergyStrip : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UEnergyStrip();

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticVisualMesh;
	UPROPERTY(EditDefaultsOnly)
	UStaticMesh* StaticMesh;
	UPROPERTY(EditDefaultsOnly)
	FColor ColorActive;
	FLinearColor ColorDefault;
	class UPowerNetwork* PowerNetwork;
	UMaterialInstanceDynamic*  MaterialInstance;


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Init(FRotator Rotator);

	void ActivateEnergyStrip(UPowerNetwork* InPowerNetwork);
	void DeactivateEnergyStrip();
};
