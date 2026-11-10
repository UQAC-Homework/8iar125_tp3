// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeath);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDamageTaken,float,CurrentHealth);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UHealthComponent : public UActorComponent
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, Category="Health")
	float MaxHealth = 10.0f;
	float CurrentHealth;
	
public:	
	// Sets default values for this component's properties
	UHealthComponent();
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	void TakeDamage(float Damage);
	
	//I would prefer it to be private to be sure it's not called by other classes
	FOnDeath OnDeath;
	FOnDamageTaken OnDamageTaken;
};
