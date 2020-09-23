// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"

class UMainUI;

/**
 * 
 */
UCLASS()
class MYPROJECT_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()
	

protected:
    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<UMainUI> MainUIBP;

public:
    UPROPERTY(VisibleAnywhere)
    UMainUI* MainUI;
    virtual void OnPossess(APawn* InPawn) override;


    //virtual void UpdateRotation(float DeltaTime) override;

};
