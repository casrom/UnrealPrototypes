// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameplayTagsManager.h"

#include "ConnectorComponent.generated.h"


UCLASS(EditInlineNew, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT_API UConnectorComponent : public USceneComponent
{
	GENERATED_BODY()


public:	
	// Sets default values for this component's properties
	UConnectorComponent();

	UPROPERTY(EditDefaultsOnly)
	class UBoxComponent* ConnectorCollider;

	UPROPERTY(VisibleAnywhere)
	int ParentEdgeIndex;

	UPROPERTY(EditAnywhere)
	TEnumAsByte<ECollisionChannel> CollisionChannel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTagContainer GameplayTags;

	UPROPERTY()
	class APanel* ParentPanel;

protected:
	virtual void BeginPlay() override;


public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Init(FVector Size, APanel* Parent, ECollisionChannel InCollisionChannel, int Reduction,  bool RegisterComponent = false);

	UFUNCTION(BlueprintCallable)
	void Enable();

	UFUNCTION(BlueprintCallable)
	void Disable();

};
