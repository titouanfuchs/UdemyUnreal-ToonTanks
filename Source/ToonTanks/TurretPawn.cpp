 // Fill out your copyright notice in the Description page of Project Settings.


#include "TurretPawn.h"
#include "TankPawn.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

 void ATurretPawn::HandleDestruction()
 {
 	Super::HandleDestruction();
 	Destroy();
 }

void ATurretPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Tank) {
		float distance = FVector::Distance(GetActorLocation(), Tank->GetActorLocation());

		CanFire = distance <= Range;

		if (CanFire) {
			RotateTurret(Tank->GetActorLocation());
		}
	}
}

void ATurretPawn::BeginPlay()
{
	Super::BeginPlay();
	Tank = Cast<ATankPawn>(UGameplayStatics::GetPlayerPawn(this, 0));

	GetWorldTimerManager().SetTimer(FireRateTimeHandle, this, &ATurretPawn::CheckFireCondition, FireRate, true);
}

void ATurretPawn::CheckFireCondition()
{
	if (CanFire) {
		Fire();
	}
}
