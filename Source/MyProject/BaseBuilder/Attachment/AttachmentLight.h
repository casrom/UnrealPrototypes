// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Attachment.h"

#include "AttachmentLight.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API AAttachmentLight : public AAttachment
{
	GENERATED_BODY()
public:
    AAttachmentLight();

    virtual void Tick(float DeltaTime) override;

    virtual void OnBuild(ABuildItem* Parent) override;

    UPanelSide* InputPanelSide;
    UPROPERTY(EditDefaultsOnly)
    class UPointLightComponent* Light;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    float Brightness;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    float MaxIntensity;
};
