// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "GameplayTagsManager.h"

#include "ConnectorComponent.generated.h"

//USTRUCT()
//struct FPanelSet
//{
//	GENERATED_BODY()
//	UPROPERTY()
//	TSet<APanel*> Panels;
//};

class APanel;

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
		//UPROPERTY(VisibleAnywhere)
	//	TMap<int, struct FPanelSet&> ConnectedPanels;

	//UPROPERTY(editAnywhere)
	//const FGameplayTag ConnectorTag = UGameplayTagsManager::Get().RequestGameplayTag("Collider.Connector.Floor");

	APanel* ParentPanel;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Init(FVector Size, APanel* Parent, ECollisionChannel InCollisionChannel, int Reduction,  bool RegisterComponent = false);

	UFUNCTION(BlueprintCallable)
	void Enable();
	UFUNCTION(BlueprintCallable)
	void Disable();
		
	//void MergeTo(UConnectorComponent* Connector);

	//void AddConnectedPanel(int _EdgeIndex, APanel* Panel);

	//void Connect(APanel* Panel);
};
