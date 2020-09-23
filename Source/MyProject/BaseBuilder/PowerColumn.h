// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Interact/InteractableInterface.h"
#include "PowerColumn.generated.h"

class APowerRedirector;
class ABuilding;

UCLASS()
class MYPROJECT_API APowerColumn : public AActor, public IInteractableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APowerColumn();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* CapTop;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* CapBottom;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	USceneComponent* Root;

	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* InteractColliderA;
	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* InteractColliderB;


	//0 natural position, -1 down, 1 up;
	int CylinderOffset = 0;
	FVector CylinderDefaultLocation;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<APowerRedirector>  PowerRedirectorBP;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	APowerRedirector* PowerRedirectorUp;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	APowerRedirector* PowerRedirectorDown;

	UFUNCTION(BlueprintImplementableEvent)
	void MoveCylinderEvent(FVector BeginLocation, FVector EndLocation, bool IsUp);
	UFUNCTION(BlueprintImplementableEvent)
	void AnimationEvent(bool Open);
	UFUNCTION(BlueprintCallable)
	void RegisterEnergyDiscs();
	void UnregisterEnergyDiscs();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/* Interactable */
	virtual void OnInteract_Implementation(UObject* TriggeredObject) override;
	virtual FText GetDescription() override;


};
