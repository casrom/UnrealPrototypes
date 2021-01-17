// Fill out your copyright notice in the Description page of Project Settings.


#include "BuilderUI.h"
#include "Components/HorizontalBox.h"
#include "Components/ListView.h"
#include "../Macros.h"




void UBuilderUI::DisplayItem(int32 Index) {
    BuildItemListView->NavigateToIndex(Index);
    UObject* item = BuildItemListView->GetSelectedItem();
    UUserWidget* widget = BuildItemListView->GetEntryWidgetFromItem(item);
    BuildItemListView->SetSelectedIndex(Index);
}