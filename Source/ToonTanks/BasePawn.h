// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

	virtual void HandleDestruction();

protected:
	void RotateTurret(FVector lookAtTarget);

	void Fire();

private:
	UPROPERTY(VisibleAnywhere)
	class UCapsuleComponent* CapsuleComponent;

	UPROPERTY(VisibleAnywhere)
		USceneComponent* ProjectileSpawnPointComponent;

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* BodyMesh;

	UPROPERTY(VisibleAnywhere)
		UStaticMeshComponent* TurretMesh;

	UPROPERTY(EditDefaultsOnly, Category="Combat")
	TSubclassOf<class AProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, Category = "Effects")
		class UParticleSystem* DeathParticle;

	UPROPERTY(EditAnywhere, Category = "Sounds")
		class USoundBase* DeathSound;

	UPROPERTY(EditAnywhere, Category = "Effects")
		TSubclassOf<class UCameraShakeBase> DeathCameraShakeClass;
};
