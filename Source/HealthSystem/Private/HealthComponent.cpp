#include "HealthComponent.h"

void UHealthComponent::OnDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
                                AController* InstigatedBy, AActor* DamageCauser)
{
	if (CurrentHealth <= 0.0f)
		return;

	CurrentHealth = FMath::Max(0.0f, CurrentHealth - Damage);

	if (OnDamageTaken.IsBound())
		OnDamageTaken.Broadcast(Damage, DamageCauser);

	if (CurrentHealth > 0.0f)
		return;

	if (OnDeath.IsBound())
		OnDeath.Broadcast(Damage, DamageCauser);

	const auto Owner = GetOwner();
	Kill(Owner);
}

void UHealthComponent::Kill(AActor* Actor)
{
	if (!Actor)
		return;

	if (Actor->IsPendingKillPending())
	{
		UE_LOGF(
			LogTemp,
			Warning,
			"Tried to kill '%ls', but it is pending a kill.",
			*Actor->GetName()
		);
		return;
	}

	const auto Pawn = Cast<APawn>(Actor);

	if (Pawn)
	{
		const auto Controller = Pawn->GetController();
		
		if (Controller)
			Controller->UnPossess();
	}

	Actor->Destroy();
}

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	MaxHealth = 20;
	CurrentHealth = MaxHealth;
}

void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	const auto Owner = GetOwner();
	check(Owner);

	Owner->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::OnDamage);
}
