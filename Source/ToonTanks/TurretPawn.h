// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "TurretPawn.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATurretPawn : public ABasePawn
{
	GENERATED_BODY()

public:
	virtual void HandleDestruction() override;
	
protected:
	virtual void Tick(float DeltaTime) override;

	virtual void BeginPlay() override;

private:
	class ATankPawn* Tank;

	UPROPERTY(EditAnywhere)
		float Range = 1000.f;

	FTimerHandle FireRateTimeHandle;
	float FireRate = 2.f;

	void CheckFireCondition();

	bool CanFire = false;
};
