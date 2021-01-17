// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"

class UMainUI;
class UActionBarComponent;

/**
 * 
 */
UCLASS()
class MYPROJECT_API AMainPlayerController : public APlayerController
{
    GENERATED_BODY()

    AMainPlayerController();

protected:
    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<UMainUI> MainUIBP;

public:
    UPROPERTY(VisibleAnywhere)
    UMainUI* MainUI;

    UPROPERTY(VisibleAnywhere)
    UActionBarComponent* ActionBar;
    
    virtual void OnPossess(APawn* InPawn) override;
    

    //virtual void UpdateRotation(float DeltaTime) override;

};
