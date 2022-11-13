// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ProjectileMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("ProjectileMesh");
	RootComponent = ProjectileMeshComponent;
	
	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
	ProjectileMovementComp->InitialSpeed = 1300.f;
	ProjectileMovementComp->MaxSpeed = 1300.f;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	ProjectileMeshComponent->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::OnHit(UPrimitiveComponent* hitComp, AActor* otherActor, UPrimitiveComponent* otherComp, FVector normalImpulse, const FHitResult& hit)
{
	//UE_LOG(LogTemp, Display, TEXT("Projectile hit : %s - %s - %s"), *(hitComp->GetName()), *(otherActor->GetName()), *(otherComp->GetName()));
	auto owner = GetOwner();

	if (owner == nullptr) return;

	auto ownerInstigator = owner->GetInstigatorController();
	auto damageTypeClass = UDamageType::StaticClass();

	if (otherActor && otherActor != this && otherActor != owner)
	{
		UGameplayStatics::ApplyDamage(otherActor, Damage, ownerInstigator, this, damageTypeClass);
		Destroy();
	} 
}

