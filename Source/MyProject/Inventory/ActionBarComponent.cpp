// Copyright 2020 Siyi Cao. All Rights Reserved.


#include "ActionBarComponent.h"
#include "../UI/MainUI.h"

UActionBarComponent::UActionBarComponent()
{
	
	PrimaryComponentTick.bCanEverTick = false;

	ActiveItemIndex = -1;
}


void UActionBarComponent::BeginPlay()
{
	Super::BeginPlay();

	IsUsed.Init(false, 5);
	ItemList.Init(FItemInfo(), 5);
	SetActiveItemIndex(0);
}


void UActionBarComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UActionBarComponent::RegisterItem(int Index, FItemInfo ItemInfo) {
	IsUsed[Index] = true;
	ItemList[Index] = ItemInfo;
	if (MainUI) {
		MainUI->UpdateActionBar(IsUsed, ItemList);
	}
	return;
}

int UActionBarComponent::FindNextAvailableIndex() {
	for (int i = 0; i < 5; i++) {
		if (!IsUsed[i]) {
			return i;
		}
	}
	return -1;
}

int UActionBarComponent::FindIndexOf(FItemInfo ItemInfo) {
	for (int i = 0; i < 5; i++) {
		if (ItemList[i].Name.EqualTo(ItemInfo.Name)) {
			return i;
		}
	}
	return -1;
}

void UActionBarComponent::SetActiveItemIndex(int32 Index) {
	if (Index >= 0 && Index < 5) {
		ActiveItemIndex = Index;
		MainUI->SetActionBarSelectorIndex(Index);
	}
}

void UActionBarComponent::NextActiveItem() {
	if (ActiveItemIndex != -1) {
		SetActiveItemIndex((ActiveItemIndex + 1) % 5);
	}
}

void UActionBarComponent::PrevActiveItem() {
	if (ActiveItemIndex != -1) {
		SetActiveItemIndex((ActiveItemIndex + 5 - 1) % 5);
	}
}

//void UActionBarComponent::ToggleActiveItem() {
//	if (ActiveItemIndex != -1) {
//		ActiveItemIndex = -1;
//		MainUI->HideActionBarSelector();
//	} else {
//
//	}
//}

