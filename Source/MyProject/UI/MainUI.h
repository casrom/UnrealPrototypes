// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainUI.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API UMainUI : public UUserWidget
{
    GENERATED_BODY()

public:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    FText Description;

    UPROPERTY(meta = (BindWidgetAnim))
    UWidgetAnimation* CrosshairActiveAnimation;

    UPROPERTY(meta = (BindWidgetAnim))
    UWidgetAnimation* CrosshairInteractAnimation;

    bool bCrosshairActive = false;
    void ActivateCrosshair();
    void DeactivateCrosshair();
    void InteractCrosshair();
};
