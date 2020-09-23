// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "Animation/AnimationAsset.h"
#include "../Interact/InteractableInterface.h"
#include "PanelButton.generated.h"


UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT_API UPanelButton : public USceneComponent, public IInteractableInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPanelButton();

	UPROPERTY(EditDefaultsOnly)
	USkeletalMeshComponent* SkeletalVisualMesh;
	UPROPERTY(EditDefaultsOnly)
	UBoxComponent* InteractCollider;
	UPROPERTY(EditDefaultsOnly)
	UAnimationAsset* PressAnimation;

	bool bActive = false;
	UMaterialInstanceDynamic* MaterialInstance;


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Init(FVector InRelativeLocation, FRotator InRelativeRotator);

	/* Interactable */
	virtual void OnInteract_Implementation(UObject* TriggeredObject) override;
	virtual FText GetDescription() override;
		
};
