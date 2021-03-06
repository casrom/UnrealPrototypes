// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Attachment.h"
#include "../../Interact/InteractableInterface.h"

#include "AttachmentDoor.generated.h"

class APanel;
/**
 * 
 */
UCLASS()
class MYPROJECT_API AAttachmentDoor : public AAttachment, public IInteractableInterface
{
	GENERATED_BODY()
	
public:
    AAttachmentDoor();

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bOpen = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UAnimMontage* DoorAnimation;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    class UBoxComponent* InteractTrigger;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool bInteractable = true;

    UPROPERTY()
    class APanel* ParentPanel;

    /* Build Item */
    virtual void OnBuild(ABuildItem* Parent) override;

    /* Interactable */
    virtual void OnInteract_Implementation(UObject* TriggeredObject, UObject* Interactor) override;
    virtual FText GetDescription() override;

};
