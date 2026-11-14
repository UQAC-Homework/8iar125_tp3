#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnBulletHit, FVector, ImpactPoint, AActor*, Actor);

/// Class that represents a generic shooter character
UCLASS()
class TP_8IAR125_TP3_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

	/// Speed of walk when the character is not aiming
	UPROPERTY(EditAnywhere, Category=Movement)
	float WalkSpeed;

	/// Speed of walk when the character is aiming
	UPROPERTY(EditAnywhere, Category=Movement)
	float AimedWalkSpeed;

	/// Is the character aiming its weapon
	UPROPERTY(VisibleAnywhere, Category=Fire)
	bool bIsAiming;

	/// Damage the character deals with its weapon
	UPROPERTY(EditAnywhere, Category=Fire, meta=(ClampMin=0))
	float WeaponDamage;

	//Starting health of the character
	UPROPERTY(EditAnywhere, Category=Health, meta=(ClampMin=0))
	float MaxHealth = 10.0f;

	//Current health of the character
	UPROPERTY(VisibleAnywhere, Category=Health, meta=(ClampMin=0))
	float CurrentHealth;

	/// Called when a bullet of this character hit something
	UPROPERTY(BlueprintAssignable, Category=Fire)
	FOnBulletHit OnBulletHit;

protected:
	/// Called when this character fires and hits something
	UFUNCTION(Category=Fire)
	virtual void OnFireHit(FVector ImpactPoint, AActor* Actor);

public:
	AShooterCharacter();

	UFUNCTION(BlueprintCallable, Category=Fire)
	FORCEINLINE bool IsAiming() const { return bIsAiming; }

	/// Starts aiming
	UFUNCTION(BlueprintCallable, Category=Fire)
	virtual void DoStartAim();

	/// Ends aiming
	UFUNCTION(BlueprintCallable, Category=Fire)
	virtual void DoEndAim();

	/// Fires a bullet
	UFUNCTION(BlueprintCallable, Category=Fire)
	virtual void DoFire(FVector StartLocation, FVector EndLocation);
	
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
};
