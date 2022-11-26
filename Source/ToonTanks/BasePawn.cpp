// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"

#include "Projectile.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
ABasePawn::ABasePawn()
{
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret"));
	ProjectileSpawnPointComponent = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawnPoint"));

	RootComponent = CapsuleComponent;
	BodyMesh->SetupAttachment(RootComponent);
	TurretMesh->SetupAttachment(BodyMesh);
	ProjectileSpawnPointComponent->SetupAttachment(TurretMesh);
}

void ABasePawn::HandleDestruction()
{
	UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation());
	UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticle, GetActorLocation());
	GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(DeathCameraShakeClass);
}

void ABasePawn::RotateTurret(const FVector lookAtTarget)
{
	const FVector toTargetVector = lookAtTarget - TurretMesh->GetComponentLocation();
	TurretMesh->SetWorldRotation(FMath::RInterpTo(TurretMesh->GetComponentRotation(), FRotator(0, toTargetVector.Rotation().Yaw, 0), GetWorld()->GetDeltaSeconds(), 10.f));
}

void ABasePawn::Fire()
{
	//DrawDebugSphere(GetWorld(), ProjectileSpawnPointComponent->GetComponentLocation(), 25, 10, FColor::Red, false, 5.f);
	auto projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, ProjectileSpawnPointComponent->GetComponentLocation(), ProjectileSpawnPointComponent->GetComponentRotation());
	projectile->SetOwner(this);
}
