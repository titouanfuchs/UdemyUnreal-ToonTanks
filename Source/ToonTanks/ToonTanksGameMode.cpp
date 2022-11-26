// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"

#include "TankPawn.h"
#include "ToonTanksPlayerController.h"
#include "TurretPawn.h"
#include "Kismet/GameplayStatics.h"

void AToonTanksGameMode::ActorDied(AActor* deadActor)
{
	if (ATankPawn* tankPawn = Cast<ATankPawn>(deadActor))
	{
		tankPawn->HandleDestruction();

		if (tankPawn->GetTankPlayerController())
		{
			tankPawn->GetTankPlayerController()->SetPlayerEnabledState(false);
			GameOver(false);
		}
	}
	else if (ATurretPawn* turretPawn = Cast<ATurretPawn>(deadActor))
	{
		turretPawn->HandleDestruction();
		TargetTurrets--;

		if (TargetTurrets <= 0)
		{
			GameOver(true);
		}
	}
}

void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();

	HandleGameStart();
}

void AToonTanksGameMode::HandleGameStart()
{
	Tank = Cast<ATankPawn>(UGameplayStatics::GetPlayerPawn(this, 0));
	ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	StartGame();

	if (ToonTanksPlayerController)
	{
		ToonTanksPlayerController->SetPlayerEnabledState(false);

		FTimerHandle playerEnableHandle;

		const FTimerDelegate playerTimerDelegate = FTimerDelegate::CreateUObject(ToonTanksPlayerController, &AToonTanksPlayerController::SetPlayerEnabledState, true);

		GetWorldTimerManager().SetTimer(playerEnableHandle, playerTimerDelegate, StartDelay, false);
	}

	TargetTurrets = GetTargetTurretsCount();
}

int32 AToonTanksGameMode::GetTargetTurretsCount() const
{
	TArray<AActor*> turrets;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATurretPawn::StaticClass(), turrets);

	return turrets.Num();
}
