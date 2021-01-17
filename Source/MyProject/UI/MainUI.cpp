// Fill out your copyright notice in the Description page of Project Settings.


#include "MainUI.h"
#include "Components/Image.h"



void UMainUI::CustomTick(float InDeltaTime) {
    if (ActionBarSelector) {
        FVector2D ActionBarSelectorCurrentTranslation = ActionBarSelector->RenderTransform.Translation;

        if (ActionBarSelectorCurrentTranslation != ActionBarSelectorTargetTranslation) {
            FVector2D Translation = FMath::Lerp(ActionBarSelectorCurrentTranslation, ActionBarSelectorTargetTranslation, InDeltaTime * 10 );
            if (Translation.Equals(ActionBarSelectorTargetTranslation, 0.01f)) {
                Translation = ActionBarSelectorTargetTranslation;
            }
            ActionBarSelector->SetRenderTranslation(Translation);
        }
    }

}


void UMainUI::ActivateCrosshair() {
    if (CrosshairActiveAnimation != NULL && !bCrosshairActive) {
        PlayAnimationForward(CrosshairActiveAnimation, 4);
        bCrosshairActive = true;
    }
}

void UMainUI::DeactivateCrosshair() {
    if (CrosshairActiveAnimation != NULL && bCrosshairActive) {
        PlayAnimationReverse(CrosshairActiveAnimation, 4);
        bCrosshairActive = false;
    }
}

void UMainUI::InteractCrosshair() {
    if (CrosshairActiveAnimation != NULL && bCrosshairActive) {
        StopAnimation(CrosshairInteractAnimation);
        PlayAnimationReverse(CrosshairInteractAnimation, 4);

    }
}

void UMainUI::SetActionBarSelectorIndex(int32 Index) {
    ActionBarSelectorTargetTranslation.X = (Index) * ActionBarItemWidth;
}

void UMainUI::ShowActionBarSelector() {
    if (ActionBarSelectorHideAnimation) {
        StopAnimation(ActionBarSelectorHideAnimation);
        PlayAnimationReverse(ActionBarSelectorHideAnimation, 2);
    }
}

void UMainUI::HideActionBarSelector() {
    if (ActionBarSelectorHideAnimation) {
        StopAnimation(ActionBarSelectorHideAnimation);
        PlayAnimationForward(ActionBarSelectorHideAnimation, 2);
    }
}