// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Attachment.h"
#include "AttachmentAirVent.generated.h"

class UPanelSide;
class USpaceChunk;

/**
 * 
 */
UCLASS()
class MYPROJECT_API AAttachmentAirVent : public AAttachment
{
	GENERATED_BODY()
	
public:
    AAttachmentAirVent();

    virtual void OnBuild(ABuildItem* Parent) override;

    virtual void Tick(float DeltaTime) override;

    UPanelSide* OutputPanelSide;
    USpaceChunk* OutputSpaceChunk;


};
