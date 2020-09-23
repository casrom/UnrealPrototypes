// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Camera/CameraComponent.h"
#include "GameplayTagContainer.h"
#include "GameplayTagsManager.h"
#include "BuilderComponent.generated.h"

class APanel;
class ABuildItem;
class AAttachment;

USTRUCT(BlueprintType)
struct FBuilderSettings {
	GENERATED_BODY()

	UPROPERTY()
	int GridSize;
	UPROPERTY()
	FVector Offset;

	FBuilderSettings() {
		GridSize = 300;
		Offset = FVector::ZeroVector;
	}
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT_API UBuilderComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBuilderComponent();

	UPROPERTY(editAnywhere)
	bool bActive;
	
	UPROPERTY(VisibleAnywhere)
	class ABuildItem* BuildItem;

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* Camera;
	
	UPROPERTY(EditAnywhere)
	FColor ColorValid;

	UPROPERTY(EditAnywhere)
	FColor ColorInvalid;

	UPROPERTY(VisibleAnywhere)
	FGameplayTag BuildPanelTag;
	UPROPERTY(VisibleAnywhere)
	FGameplayTag BuildAttachmentTag;
	UPROPERTY(VisibleAnywhere)
	FGameplayTag BuildPanelWallTag;
	UPROPERTY(VisibleAnywhere)
	FGameplayTag BuildPanelFloorTag;

	UPROPERTY(EditAnywhere)
	UMaterial* BluePrintMaterial;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray< TSubclassOf<ABuildItem> > BuildItemsBP;
	UPROPERTY()
	TArray<ABuildItem*> BuildItems;

	FBuilderSettings BuilderSettings;

private:
	FVector BuildLocation;
	FRotator BuildRotator;
	FTransform BuildTransform;
	UPrimitiveComponent* ActiveConnector;
	AActor* ActiveActor;
	bool bBuildable;

	//ABuildItem* BuildItemDisplay;
	APanel* BuildPanel;
	AAttachment* BuildAttachment;

	int ActiveBuildItemIndex = 0;

	void SnapToGrid(FVector* Location);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	UMaterialInstanceDynamic* MaterialInstance;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void BeginDestroy() override;


	UFUNCTION(BlueprintCallable)
	void SetCamera(UCameraComponent* _Camera);
	UFUNCTION(BlueprintCallable)
	void GenerateBuildItems();


	void SetActiveBuildItem(int Index, bool bForce = false);

	void NextBuildItem();
	void PrevBuildItem();
	void Build();
	void ToggleBuilder();
	
	void RotateBuildItem();
};
