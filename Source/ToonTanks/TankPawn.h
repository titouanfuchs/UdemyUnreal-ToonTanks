// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "ToonTanksPlayerController.h"
#include "TankPawn.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATankPawn : public ABasePawn
{
	GENERATED_BODY()

public:
	ATankPawn();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void HandleDestruction() override;
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category = "Components")
		class UCameraComponent* CameraComp;

	UPROPERTY(EditAnywhere, Category = "Components")
		class USpringArmComponent* SpringArmComp;

	UPROPERTY(EditAnywhere, Category = "Player Movement")
		float PlayerSpeed = 6.0;

	void Move(float value);

	void Rotate(float value);

	AToonTanksPlayerController* TankPlayerController;

	bool IsPlayerAlive = true;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	AToonTanksPlayerController* GetTankPlayerController() const { return TankPlayerController; }

	bool GetIsPlayerAlive() const { return IsPlayerAlive; }
};


