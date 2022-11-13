// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	Health = MaxHealth;

	ToonTanksGameModeRef = Cast<AToonTanksGameMode>(UGameplayStatics::GetGameMode(this));

	if (ToonTanksGameModeRef)
	{
		UE_LOG(LogTemp, Warning, TEXT("Found GameMode"));
	}
	
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::DamageTaken(AActor* damagedActor, float damage, const UDamageType* damageType,
	AController* instigator, AActor* damageCauser)
{
	if (damage <= 0) return;

	Health -= damage;
	UE_LOG(LogTemp, Warning, TEXT("Health : %f"), Health);

	if (Health <= 0.f)
	{
		UE_LOG(LogTemp, Warning, TEXT("Actor died %s"), *GetOwner()->GetName());
		if (ToonTanksGameModeRef)
		{
			ToonTanksGameModeRef->ActorDied(GetOwner());
		}
	}
}

