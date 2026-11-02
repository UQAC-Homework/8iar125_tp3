// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ShooterAIController.generated.h"

/**
 * 
 */
UCLASS()
class TP_8IAR125_TP3_API AShooterAIController : public AAIController
{
	GENERATED_BODY()
	
public:

	AShooterAIController(const FObjectInitializer& ObjectInitializer);
	
protected:
	
	virtual void OnPossess(APawn* InPawn) override;
	
	UPROPERTY(EditDefaultsOnly, Category="AI")
	TObjectPtr<UBehaviorTree> TreeAsset;
	
};
