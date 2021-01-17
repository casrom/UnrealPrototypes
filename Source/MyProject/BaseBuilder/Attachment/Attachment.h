// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "../BuildItem.h"

#include "Attachment.generated.h"

class APanel;
class UPanelSide;

UCLASS()
class MYPROJECT_API AAttachment : public ABuildItem
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAttachment();

	UPROPERTY()
	ABuildItem* AttachmentParent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void OnBuild(ABuildItem* Parent);

	UPanelSide* FindPanelSide();

};
