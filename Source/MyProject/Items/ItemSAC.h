// Copyright 2020 Siyi Cao. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "../Inventory/Item.h"
#include "ItemSAC.generated.h"

/**
 * 
 */
UCLASS()
class MYPROJECT_API AItemSAC : public AItem
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

	bool Attached;
	bool AttachComplete;
	bool Ejected;
	FRotator TargetRotator;
	FVector ImpactNormal;
	float TimeSinceAttached;


public:
	AItemSAC();

	virtual void Tick(float DeltaTime) override;

	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	class UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(EditDefaultsOnly)
	class USphereComponent* BaseCollider;

	UPROPERTY(EditDefaultsOnly, Category = Claw)
	class USkeletalMeshComponent* Claw;

	UPROPERTY(EditDefaultsOnly, Category = Claw)
	class UAnimationAsset* ClawCloseAnim;

	UPROPERTY(EditDefaultsOnly)
	UMaterialInterface* SACBodyMaterial;
	UPROPERTY()
	UMaterialInstanceDynamic* BodyDynamicMaterial;

	UPROPERTY(EditDefaultsOnly, Category = SAC)
	float ChargeTime;

	UPROPERTY(EditDefaultsOnly, Category = SAC)
	float PreEjectDelay;

	UPROPERTY(EditDefaultsOnly)
	class UParticleSystemComponent* EjectParticle;

	/** called when projectile hits something */
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
