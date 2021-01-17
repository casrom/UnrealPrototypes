// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../Inventory/Item.h"
#include "Layout/Geometry.h"

#include "MainUI.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API UMainUI : public UUserWidget
{
    GENERATED_BODY()

private:

public:

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    FText Description;

    UPROPERTY(meta = (BindWidgetAnim))
    UWidgetAnimation* CrosshairActiveAnimation;

    UPROPERTY(meta = (BindWidgetAnim))
    UWidgetAnimation* CrosshairInteractAnimation;

    UPROPERTY(meta = (BindWidgetAnim))
    UWidgetAnimation* ActionBarSelectorHideAnimation;


    UPROPERTY(meta = (BindWidget))
    class UImage* ActionBarSelector;

    bool bCrosshairActive = false;
    void ActivateCrosshair();
    void DeactivateCrosshair();
    void InteractCrosshair();

    /* Action Bar */
    UFUNCTION(BlueprintImplementableEvent)
    void SetActionBarItemInfo(int32 Index, FItemInfo ItemInfo);

    UFUNCTION(BlueprintImplementableEvent)
    void UpdateActionBar(const TArray<bool> &IsUsed, const TArray<FItemInfo> &ItemInfos);

    UFUNCTION(BlueprintCallable)
    void CustomTick(float InDeltaTime);

    UPROPERTY(EditAnywhere)
    FVector2D ActionBarSelectorTargetTranslation;
    UPROPERTY(EditDefaultsOnly)
    float ActionBarItemWidth;


    void SetActionBarSelectorIndex(int32 Index);
    void ShowActionBarSelector();
    void HideActionBarSelector();

};
