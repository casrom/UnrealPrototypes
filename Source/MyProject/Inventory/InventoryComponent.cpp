// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryComponent.h"
#include "Kismet/GameplayStatics.h"
#include "../MainPlayerController.h"
#include "../UI/MainUI.h"
#include "ActionBarComponent.h"

UInventoryComponent::UInventoryComponent()
{

	PrimaryComponentTick.bCanEverTick = false;

}


void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	AMainPlayerController* controller = Cast<AMainPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	ActionBar = nullptr;
	if (controller) ActionBar = controller->ActionBar;
}


void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInventoryComponent::AddItem(FItemInfo NewItemInfo) {

	int index = -1;

	for (auto &ItemInfo : ItemList) {
		if (ItemInfo.Name.EqualTo(NewItemInfo.Name)) {
			ItemInfo.Count += NewItemInfo.Count;
			if (ActionBar) {
				index = ActionBar->FindIndexOf(ItemInfo);
				if (index != -1) {
					ActionBar->RegisterItem(index, ItemInfo);
				}
			}
			return;
		}
	}
	//add as new item
	ItemList.Add(NewItemInfo);
	if (ActionBar) {
		index = ActionBar->FindNextAvailableIndex();
		if (index != -1) {
			ActionBar->RegisterItem(index, NewItemInfo);
		}
		
	}


}

