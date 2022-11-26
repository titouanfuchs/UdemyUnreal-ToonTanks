// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPawn.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

ATankPawn::ATankPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComp->SetupAttachment(RootComponent);

	CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComp->SetupAttachment(SpringArmComp);
}

// Called to bind functionality to input
void ATankPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATankPawn::Move);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATankPawn::Rotate);
	PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed,this, &ATankPawn::Fire);
}

void ATankPawn::HandleDestruction()
{
	Super::HandleDestruction();
	IsPlayerAlive = false;
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
}

void ATankPawn::BeginPlay()
{
	Super::BeginPlay();
	TankPlayerController = Cast<AToonTanksPlayerController>(GetController());
}

void ATankPawn::Move(float value)
{
	//UE_LOG(LogTemp, Display, TEXT("Axis value %f"), value);
	AddActorLocalOffset(FVector(value * GetWorld()->GetDeltaSeconds() * PlayerSpeed, 0, 0), true);
}

void ATankPawn::Rotate(float value)
{
	AddActorLocalRotation(FRotator(0, value * GetWorld()->GetDeltaSeconds() * PlayerSpeed / 2, 0), true);
}

// Called every frame
void ATankPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (TankPlayerController) {

		FHitResult hitResult;
		bool hit = TankPlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, hitResult);

		if (hit) {
			//DrawDebugSphere(GetWorld(), hitResult.ImpactPoint, 25, 12, FColor::Blue);

			RotateTurret(hitResult.ImpactPoint);
		}
	}
}
