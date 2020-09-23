// Fill out your copyright notice in the Description page of Project Settings.


#include "MainUI.h"

void UMainUI::ActivateCrosshair() {
    if (CrosshairActiveAnimation != NULL && !bCrosshairActive) {
        PlayAnimationForward(CrosshairActiveAnimation, 2);
        bCrosshairActive = true;
    }
}

void UMainUI::DeactivateCrosshair() {
    if (CrosshairActiveAnimation != NULL && bCrosshairActive) {
        PlayAnimationReverse(CrosshairActiveAnimation);
        bCrosshairActive = false;
    }
}

void UMainUI::InteractCrosshair() {
    if (CrosshairActiveAnimation != NULL && bCrosshairActive) {
        PlayAnimationReverse(CrosshairInteractAnimation, 1.5);
    }
}
