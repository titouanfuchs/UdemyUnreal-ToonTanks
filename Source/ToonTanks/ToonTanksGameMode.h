// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanksGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTanksGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	void ActorDied(AActor* deadActor);
	

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();

	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool bWonGame);
	
private:
	class ATankPawn* Tank;

	class AToonTanksPlayerController* ToonTanksPlayerController;

	float StartDelay = 5.f;

    void HandleGameStart();

	int32 TargetTurrets = 0;
	int32 GetTargetTurretsCount() const;
};
