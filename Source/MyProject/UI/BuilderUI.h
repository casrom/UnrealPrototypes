// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BuilderUI.generated.h"

class UHorizontalBox;
class UListView;
class ABuildItem;
/**
 * 
 */
UCLASS()
class MYPROJECT_API UBuilderUI : public UUserWidget
{
	GENERATED_BODY()


public:

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UListView* BuildItemListView;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	FText Description;

	UFUNCTION(BlueprintImplementableEvent)
	void AddBuildItem(ABuildItem* NewItem);

	void DisplayItem(int32 Index);
	
};
