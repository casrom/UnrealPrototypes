// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"
#include "UI/MainUI.h"
#include "Blueprint/UserWidget.h"
#include "Macros.h"
#include "Inventory/ActionBarComponent.h"

AMainPlayerController::AMainPlayerController() {
    ActionBar = CreateDefaultSubobject<UActionBarComponent>(TEXT("ActionBar"));
}

void AMainPlayerController::OnPossess(APawn* InPawn) {
    Super::OnPossess(InPawn);
    if (MainUIBP != NULL && MainUI == NULL) {
        MainUI = CreateWidget<UMainUI>(this, MainUIBP);
        MainUI->AddToViewport();
    }

    if (ActionBar && MainUI) {
        ActionBar->MainUI = MainUI;
    }
}

