// Copyright 2020 Siyi Cao. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "Item.h"

#include "ActionBarComponent.generated.h"


class UMainUI;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT_API UActionBarComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UActionBarComponent();

	UPROPERTY(EditAnywhere)
	TArray<FItemInfo> ItemList;

	TArray<bool> IsUsed;

	UPROPERTY()
	UMainUI* MainUI;

private:
	int ActiveItemIndex;
	

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	/// <summary>
	/// Register an item to the action bar
	/// </summary>
	/// <param name="Index">of the slot in the bar</param>
	/// <param name="ItemInfo"> of the item to be registered</param>
	void RegisterItem(int Index, FItemInfo ItemInfo);

	/// <summary>
	/// Find the next empty slot in the action bar
	/// </summary>
	/// <returns>-1 if no empty slot available</returns>
	int FindNextAvailableIndex();

	int FindIndexOf(FItemInfo ItemInfo);

	void SetActiveItemIndex(int32 Index);

	void NextActiveItem();

	void PrevActiveItem();

	//void ToggleActiveItem();
};
