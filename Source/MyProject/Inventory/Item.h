// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Interact/InteractableInterface.h"

#include "Item.generated.h"


USTRUCT(BlueprintType)
struct FItemInfo {
	GENERATED_BODY()
	FItemInfo(): Count(1) {
		Name = FText::FromString("Unknown Item");
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Name;
	//UPROPERTY(EditAnywhere, BlueprintReadWrite)
	//UStaticMesh* StaticVisualMesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Count;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AItem> ItemBP;

};


UCLASS()
class MYPROJECT_API AItem : public AActor, public IInteractableInterface
{
	GENERATED_BODY()
	
public:	

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FItemInfo Info;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UStaticMeshComponent* VisualMesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UBoxComponent* InteractTrigger;

	AItem();

protected:

	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	
	/* Interactable */
	virtual void OnInteract_Implementation(UObject* TriggeredObject, UObject* Interactor) override;
	virtual FText GetDescription() override;

};
