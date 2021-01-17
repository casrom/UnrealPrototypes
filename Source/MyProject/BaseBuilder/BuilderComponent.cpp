// Fill out your copyright notice in the Description page of Project Settings.
#include "BuilderComponent.h"
#include "Building.h"
#include "Globals.h"
#include "BuildItem.h"
#include "Panel.h"
#include "Attachment/Attachment.h"
#include "../UI/BuilderUI.h"
#include "ConnectorComponent.h"
#include "DrawDebugHelpers.h"


// Sets default values for this component's properties
UBuilderComponent::UBuilderComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	ColorValid = FColor::Cyan;
	ColorInvalid = FColor::Red;

	BuildPanelTag = UGameplayTagsManager::Get().RequestGameplayTag("BuildItem.Panel");
	BuildAttachmentTag = UGameplayTagsManager::Get().RequestGameplayTag("BuildItem.Attachment");
	BuildPanelWallTag = UGameplayTagsManager::Get().RequestGameplayTag("BuildItem.Panel.Wall");
	BuildPanelFloorTag = UGameplayTagsManager::Get().RequestGameplayTag("BuildItem.Panel.Floor");
}


// Called when the game starts
void UBuilderComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	//Camera = Cast<UCameraComponent>(GetOwner()->GetComponentByClass(UCameraComponent::StaticClass()));
	if (BuilderUIBP != nullptr && BuilderUI == nullptr) {
		BuilderUI = CreateWidget<UBuilderUI>(GetWorld(), BuilderUIBP);
	}

	GenerateBuildItems();
	ActiveBuildItemIndex = 0;
}

void UBuilderComponent::BeginDestroy() {
	Super::BeginDestroy();
	//for (auto Item : BuildItems) {
	//	if (Item && Item->IsRooted())
	//		Item->RemoveFromRoot();
	//}
}


// Called every frame
void UBuilderComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{

	ActiveConnector = NULL;
	ActiveActor = NULL;
	
	if (Camera && BuildItem) {
		Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

		FHitResult Hit;
		float RayLength = 1000;

		FVector CameraLocation = Camera->GetComponentLocation();
		FVector StartLocation = CameraLocation;
		FVector EndLocation = CameraLocation + (Camera->GetForwardVector() * RayLength);
		BuildTransform = FTransform(EndLocation);
		BuildTransform.SetRotation(BuildRotator.Quaternion());
		//BuildRotation = BuildItem->GetActorRotation();
		FCollisionQueryParams CollisionParams;
		CollisionParams.AddIgnoredActor(GetOwner());

		bBuildable = false;

		//if (GetWorld()->LineTraceSingleByProfile(Hit, StartLocation, EndLocation, "Builder", CollisionParams)) {

		if (GetWorld()->LineTraceSingleByChannel(Hit, StartLocation, EndLocation, BuildItem->BuildItemInfo.CollisionChannel, CollisionParams)){
			//DEBUGMESSAGE("hit %s %x\n", *Hit.GetComponent()->GetAttachParent()->GetFName().ToString(), Hit.GetComponent()->GetAttachmentRootActor()->GetUniqueID() == BuildItem->GetUniqueID());
			//DEBUGMESSAGE("hit %s\n", *Hit.GetComponent()->GetAttachParent()->GetComponentRotation().ToString());
			//DEBUGMESSAGE("hit %s\n", *Hit.GetComponent()->GetAttachParent()->GetComponentRotation().Quaternion().GetUpVector().ToString());
			if (BuildItem->BuildItemInfo.BuildItemTag.MatchesTag(BuildPanelTag)) {
				//DEBUGMESSAGE("PANEL\n");
				if (BuildItem->BuildItemInfo.BuildItemTag.MatchesTag(BuildPanelWallTag)) {
					//Align forward of BuildTransform with that of the panel
					//BuildTransform.Rotator();
					//DEBUGMESSAGE("ISWALL\n");
					FQuat Rot = FRotationMatrix::MakeFromZX(Hit.GetComponent()->GetAttachParent()->GetComponentRotation().Quaternion().GetUpVector(), FVector::UpVector).ToQuat();
					BuildTransform.SetRotation(Rot);
					//BuildTransform.SetRotation(FRotator(BuildTransform.Rotator().Pitch, BuildTransform.Rotator().Yaw, BuildTransform.Rotator().Roll).Quaternion()); }
				}
				bBuildable = true;
				BuildTransform = Hit.GetComponent()->GetAttachParent()->GetComponentTransform();
			}
			ActiveConnector = Hit.GetComponent();
			ActiveActor = Hit.GetActor();
			//DEBUGMESSAGE("%s - %s", *BuildItem->BuildItemInfo.BuildItemTag.ToString(), *BuildAttachmentTag.ToString());
			if (BuildItem->BuildItemInfo.BuildItemTag.MatchesTag(BuildAttachmentTag)) {
				UConnectorComponent* CC = Cast<UConnectorComponent>(ActiveConnector->GetAttachParent());
				//DEBUGMESSAGE("hit %x\n", CC==NULL);
				if (CC && BuildItem->BuildItemInfo.BuildItemTag.MatchesAny(CC->GameplayTags)) {
					//DEBUGMESSAGE("hit\n");
					bBuildable = true;
					BuildTransform = Hit.GetComponent()->GetAttachParent()->GetComponentTransform();
				}
			}
		} else if (GetWorld()->LineTraceSingleByChannel(Hit, StartLocation, EndLocation, ECollisionChannel::ECC_WorldStatic, CollisionParams)) {
			//DEBUGMESSAGE("bBuildableAnywhere\n");
			if (Hit.GetComponent()->GetAttachParent() != nullptr)
				//DEBUGMESSAGE("hit %s\n", *Hit.GetComponent()->GetAttachParent()->GetFName().ToString())
			if (BuildItem->BuildItemInfo.bBuildableAnywhere) {
				//DEBUGMESSAGE("bBuildableAnywhere\n");
				bBuildable = true;
			}
			BuildTransform.SetTranslation(Hit.Location);
			BuildTransform.SetRotation(BuildRotator.Quaternion());
			if (BuildItem->BuildItemInfo.BuildItemTag.MatchesTag(BuildPanelFloorTag)) {
				//elevate floor if built on ground
				//BuildTransform.SetTranslation(BuildTransform.GetTranslation() + FVector(0, 0, PANEL_THICKNESS/2));
			}
		}


		

		//BuildLocation += BuilderSettings.Offset;
		//SnapToGrid(&BuildLocation);
		
		if (BuildItem->bOverlap) {
			//DEBUGMESSAGE("OVERLAP\n");  
			bBuildable = false;
		}

		if (BuildItem->BuildItemInfo.BuildItemTag.MatchesTag(BuildPanelTag)) {
			if (!BuildItem->BuildItemInfo.BuildItemTag.MatchesTag(BuildPanelWallTag)) BuildTransform.SetRotation(FRotator(0, BuildTransform.Rotator().Yaw, 0).Quaternion());
		}

		BuildItem->SetActorTransform(BuildTransform);
		//DEBUGMESSAGE("%s/n", *BuildTransform.ToString());
		if (MaterialInstance != NULL) {
			if (!bBuildable) {
				MaterialInstance->SetVectorParameterValue("BaseColor", ColorInvalid);
			} else {
				MaterialInstance->SetVectorParameterValue("BaseColor", ColorValid);
			}
		}

		//BuildItem->SetActorRotation(BuildItemRotation);

		//DrawDebugLine(GetWorld(), StartLocation, BuildItemLocation, FColor::Green, false, 1, 0, 1.f);
	}
	// ...
}


void UBuilderComponent::SnapToGrid(FVector* Location) {
	int step = BuilderSettings.GridSize;
	Location->X = ((int)roundf(Location->X) / step * step);
	Location->Y = ((int)roundf(Location->Y) / step * step);
	Location->Z = ((int)roundf(Location->Z) / step * step);
	//return Location;
}

void UBuilderComponent::SetCamera(UCameraComponent* _Camera) {
	Camera = _Camera;
}

void UBuilderComponent::NextBuildItem()
{
	DEBUGMESSAGE("NEXT %d", BuildItemsBP.Num())
	if (BuilderUI != nullptr) {
		//BuilderUI->DisplayNextItem();
		
	}
	if(BuildItemsBP.Num()>0)
		SetActiveBuildItem((ActiveBuildItemIndex + 1) % BuildItemsBP.Num());
}

void UBuilderComponent::PrevBuildItem()
{
	if (BuildItemsBP.Num() > 0)
		SetActiveBuildItem((ActiveBuildItemIndex - 1 + BuildItemsBP.Num()) % BuildItemsBP.Num());
}

void UBuilderComponent::GenerateBuildItems() {
	BuildItems.Empty();
	for (auto BuildItemBP : BuildItemsBP) {
		ABuildItem* Item = (ABuildItem*)GetWorld()->SpawnActor(BuildItemBP);
		Item->InitBuildBlueprint();
	    Item->SetActorEnableCollision(false);
		Item->SetActorTickEnabled(false);
		Item->SetActorHiddenInGame(true);
		Item->AttachToActor(GetOwner(), FAttachmentTransformRules::KeepRelativeTransform);
		BuildItems.Add(Item);
		BuilderUI->AddBuildItem(Item);
	}
}

void UBuilderComponent::SetActiveBuildItem(int Index, bool bForce) {
	check(Index >= 0 && Index < BuildItemsBP.Num());
	BuildPanel = NULL;
	BuildAttachment = NULL;
	if ((Index == ActiveBuildItemIndex&&!bForce) || !bActive) return;
	if (BuildItem != NULL) {
		BuildItem->SetActorEnableCollision(false);
		BuildItem->SetActorHiddenInGame(true);
	}
	BuildItem = NULL;
	ActiveBuildItemIndex = Index;
	if (BuildItemsBP[ActiveBuildItemIndex] != NULL) {
		if (BuildItems.Num() > 0)
			BuildItem = BuildItems[ActiveBuildItemIndex];
		//BuildItem = (ABuildItem*)GetWorld()->SpawnActor(BuildItemsBP[ActiveBuildItemIndex]);
		//BuildItem = ABuildItem::SpawnBuildItemDisplay(GetWorld(), BuildItems[ActiveBuildItemIndex]);
		if (BuildItem != NULL) {
			//DEBUGMESSAGE("%d", ActiveBuildItemIndex);
			BuilderUI->DisplayItem(Index);
			BuildItem->SetActorHiddenInGame(false);
			BuildItem->SetActorEnableCollision(true);
			if (BuildItem->StaticVisualMesh != NULL) {
				BuildItem->StaticVisualMesh->SetMaterial(0, BluePrintMaterial);
				MaterialInstance = BuildItem->StaticVisualMesh->CreateDynamicMaterialInstance(0);
			} else if (BuildItem->SkeletalVisualMesh != NULL) {
				BuildItem->SkeletalVisualMesh->SetMaterial(0, BluePrintMaterial);
				MaterialInstance = BuildItem->SkeletalVisualMesh->CreateDynamicMaterialInstance(0);
			}
		}
		BuildRotator = BuildItem->BuildItemInfo.DefaultRotator;
		BuildPanel = Cast<APanel>(BuildItem);
		BuildAttachment = Cast<AAttachment>(BuildItem);
	}

}

void UBuilderComponent::Build() {
	if (!bBuildable || !bActive) return;

	ABuildItem *Item = (ABuildItem*) GetWorld()->SpawnActor(BuildItemsBP[ActiveBuildItemIndex]);
	Item->SetActorTransform(BuildTransform);
	if (ActiveConnector != NULL) {
		UConnectorComponent* CC = Cast<UConnectorComponent>(ActiveConnector->GetAttachParent());
		if (CC != NULL) {
			//DEBUGMESSAGE("!!!");
			CC->Disable();
			Item->InUseConnector = CC;
		}
	}

	APanel* Panel = Cast<APanel>(Item);

	/* Panel */
	if (Panel != NULL) {
		ABuilding* Building = NULL;
		if (ActiveConnector != NULL && ActiveActor != NULL) {
			APanel* TargetPanel = Cast<APanel>(ActiveActor);
			if (TargetPanel != NULL && Panel != NULL) {
				Panel->SweepAll();
				//DEBUGMESSAGE("SWEEP\n");
				if (TargetPanel->Building != NULL) {
					Building = TargetPanel->Building;
				}
			}
		} else {
			Building = (ABuilding*)GetWorld()->SpawnActor(ABuilding::StaticClass(), &BuildTransform);
		}
		if (Building != NULL) {
			Building->AddPanel(*Panel);
		}
	}

	Item->OnBuild(Cast<ABuildItem>(ActiveActor));


	
}

void UBuilderComponent::ToggleBuilder() {
	if (bActive) {
		bActive = false;
		if (BuildItem != NULL) BuildItem->SetActorHiddenInGame(true);
		BuildItem = NULL;
		BuildPanel = NULL;
		SetActive(false);
		if (BuilderUI != nullptr) {
			BuilderUI->RemoveFromViewport();
		}
	} else {
		SetActive(true);
		bActive = true;
		int NewIndex = FMath::Min(ActiveBuildItemIndex, BuildItemsBP.Num()-1);
		if (BuilderUI != nullptr) {
			BuilderUI->AddToViewport();
		}
		if (BuildItemsBP.Num() > 0) SetActiveBuildItem(NewIndex, true);
		
	}
}

void UBuilderComponent::RotateBuildItem() {

}
