#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnDamageTaken, float, Amount, AActor*, Source);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDeath, AActor*, Source);

/// Component responsible to manage the health of an actor
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class HEALTHSYSTEM_API UHealthComponent : public UActorComponent
{
private:
	GENERATED_BODY()

	/// Maximum health of the actor
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Health, meta=(ClampMin=0, AllowPrivateAccess=true))
	float MaxHealth;

	/// Current health of the actor
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Health, meta=(ClampMin=0, AllowPrivateAccess=true))
	float CurrentHealth;

	/// Called when the actor takes any damage
	UFUNCTION()
	void OnDamage(
		AActor* DamagedActor,
		float Damage,
		const UDamageType* DamageType,
		AController* InstigatedBy,
		AActor* DamageCauser
	);

	/// Kills the given actor
	void Kill(AActor* Actor);

public:
	UHealthComponent();

	virtual void BeginPlay() override;
	
	/// Called when this actor takes damage from a given source
	UPROPERTY(BlueprintAssignable, Category=Health, meta=(ClampMin=0))
	FOnDamageTaken OnDamageTaken;

	/// Called when this actor dies
	UPROPERTY(BlueprintAssignable, Category=Health, meta=(ClampMin=0))
	FOnDeath OnDeath;
};
