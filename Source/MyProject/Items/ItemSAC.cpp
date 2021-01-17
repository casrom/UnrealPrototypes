// Copyright 2020 Siyi Cao. All Rights Reserved.


#include "ItemSAC.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"

#include "../Macros.h"
#include "DrawDebugHelpers.h"

AItemSAC::AItemSAC() {

	BaseCollider = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	BaseCollider->InitSphereRadius(5.0f);
	BaseCollider->SetupAttachment(VisualMesh);

	Claw = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Claw"));
	Claw->SetupAttachment(VisualMesh);

	EjectParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("EjectParticle"));
	EjectParticle->SetupAttachment(VisualMesh);

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	//ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 2000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;
	Attached = false;
	AttachComplete = false;
	TimeSinceAttached = 0;
	Ejected = false;
	PrimaryActorTick.bCanEverTick = true;

	ChargeTime = 2.5;
	PreEjectDelay = 0.5;

}

void AItemSAC::BeginPlay() {
	Super::BeginPlay();
	BaseCollider->SetRelativeLocation(FVector(10,0,0));
	Claw->SetRelativeLocation(FVector(0, 0, 0));
	EjectParticle->SetRelativeLocation(FVector(10, 0, 0));
	EjectParticle->Deactivate();

	BaseCollider->OnComponentHit.AddDynamic(this, &AItemSAC::OnHit);

	BodyDynamicMaterial = UMaterialInstanceDynamic::Create(SACBodyMaterial, this);

	VisualMesh->SetMaterialByName("Body", BodyDynamicMaterial);
	if (BodyDynamicMaterial) BodyDynamicMaterial->SetScalarParameterValue("Completion", 0);
}

void AItemSAC::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit) {
	if (!Attached && (OtherActor != NULL) && (OtherActor != this) && (OtherComp != nullptr)) {
		//DEBUGMESSAGE("hit %s %s", *OtherActor->GetName(), *Hit.ImpactPoint.ToString());
		DisableComponentsSimulatePhysics();
		ProjectileMovement->Deactivate();
		//SetActorEnableCollision(false);
		FVector Diff =  Hit.ImpactNormal - FVector(-1, 0, 0);
		Diff.Normalize();
		//AttachToActor(OtherActor, FAttachmentTransformRules::KeepWorldTransform);

		//SetActorRotation(FRotationMatrix::MakeFromX(-Hit.ImpactNormal).Rotator(), ETeleportType::ResetPhysics);
		SetActorLocation(Hit.ImpactPoint + Hit.ImpactNormal * 10, false, nullptr, ETeleportType::ResetPhysics);

		//DrawDebugLine(GetWorld(), Hit.ImpactPoint, Hit.ImpactPoint + Hit.ImpactNormal * 30, FColor::Red, true);
		Attached = true;
		TargetRotator = FRotationMatrix::MakeFromX(-Hit.ImpactNormal).Rotator();
		ImpactNormal = Hit.ImpactNormal;
		BaseCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		if (ClawCloseAnim) {
			Claw->PlayAnimation(ClawCloseAnim, false);
		}
	}

}

void AItemSAC::Tick(float DeltaTime) {
	if (!AttachComplete && Attached) {
		TimeSinceAttached += DeltaTime;
		FRotator CurrentRotator = GetActorRotation();
		if (!CurrentRotator.Equals(TargetRotator, 0.2f) && (TimeSinceAttached < 0.5)) {
			CurrentRotator = FMath::Lerp(CurrentRotator, TargetRotator, DeltaTime * 10);
			SetActorRotation(CurrentRotator, ETeleportType::ResetPhysics);
		} else {
			AttachComplete = true;
			SetActorRotation(TargetRotator, ETeleportType::ResetPhysics);
			TimeSinceAttached = 0;
		}
	}
	if (AttachComplete && !Ejected) {
		//DEBUGMESSAGE("%f", TimeSinceAttached);
		//Charging
		if (BodyDynamicMaterial) BodyDynamicMaterial->SetScalarParameterValue("Completion", TimeSinceAttached/ChargeTime);

		TimeSinceAttached += DeltaTime;
		if (TimeSinceAttached > ChargeTime + PreEjectDelay) {
			VisualMesh->SetSimulatePhysics(true);
			VisualMesh->SetPhysicsLinearVelocity(ImpactNormal * 1000);
			Ejected = true;
			//PrimaryActorTick.SetTickFunctionEnable(false);
			Claw->SetHiddenInGame(true, true);
		}
		if (!Ejected && TimeSinceAttached > ChargeTime) {
			EjectParticle->Activate();
		}
	}

	if (Ejected && EjectParticle->IsActive() && TimeSinceAttached > ChargeTime + PreEjectDelay + 0.1) {
		EjectParticle->Deactivate();
	} else {
		TimeSinceAttached += DeltaTime;
	}



}