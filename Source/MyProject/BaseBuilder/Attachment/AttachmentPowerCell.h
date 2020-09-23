// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Attachment.h"
#include "AttachmentPowerCell.generated.h"

class UPanelSide;
/**
 * 
 */
UCLASS()
class MYPROJECT_API AAttachmentPowerCell : public AAttachment
{
	GENERATED_BODY()
	
public:
    AAttachmentPowerCell();

    virtual void Tick(float DeltaTime) override;

    virtual void OnBuild(ABuildItem* Parent) override;

    UPanelSide* OutputPanelSide;

};
