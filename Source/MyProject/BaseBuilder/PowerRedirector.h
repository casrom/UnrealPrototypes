// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Interact/InteractableInterface.h"
#include "PowerRedirector.generated.h"


UCLASS()
class MYPROJECT_API APowerRedirector : public AActor, public IInteractableInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APowerRedirector();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMeshComponent* StaticVisualMesh;

	UFUNCTION(BlueprintImplementableEvent)
	void RotateEvent(FRotator BeginRotation, FRotator EndRotation);
	UFUNCTION(BlueprintImplementableEvent)
	void MoveEvent (FVector BeginLocation, FVector EndLocation);

	int RotationIndex = 0;
	class UPanelSide* PanelSide;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/* Interactable */
	virtual void OnInteract_Implementation(UObject* TriggeredObject, UObject* Interactor) override;
	virtual FText GetDescription() override;

	bool FindAndRegisterPanelSide(FVector SidesCenter, FVector Direction);
	void UnRegisterPanelSide();
};
