// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class USoundBase;

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* ProjectileMeshComponent;

	UPROPERTY(VisibleAnywhere)
		class UProjectileMovementComponent* ProjectileMovementComp;

	UPROPERTY(EditAnywhere)
		class UParticleSystemComponent* ParticleTrail;

	UFUNCTION()
		void OnHit(UPrimitiveComponent* hitComp, AActor* otherActor, UPrimitiveComponent* otherComp, FVector normalImpulse, const FHitResult& hit);

	UPROPERTY(EditAnywhere)
		float Damage = 50.f;

	UPROPERTY(EditAnywhere)
		class UParticleSystem* HitParticles;

	UPROPERTY(EditAnywhere, Category="Sounds")
		USoundBase* LaunchSound;

	UPROPERTY(EditAnywhere, Category = "Sounds")
		USoundBase* HitSound;

	UPROPERTY(EditAnywhere, Category="Effects")
		TSubclassOf<class UCameraShakeBase> HitCameraShakeClass;
};
