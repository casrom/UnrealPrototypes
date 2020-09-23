// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"
#include "UI/MainUI.h"
#include "Blueprint/UserWidget.h"
#include "Macros.h"

void AMainPlayerController::OnPossess(APawn* InPawn) {
    Super::OnPossess(InPawn);
    if (MainUIBP != NULL && MainUI == NULL) {
        MainUI = CreateWidget<UMainUI>(this, MainUIBP);
        MainUI->AddToViewport();
    }
}

