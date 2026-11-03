// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "ShooterAIController.generated.h"

/**
 * 
 */
UCLASS()
class TP_8IAR125_TP3_API AShooterAIController : public AAIController
{
	GENERATED_BODY()
	
	// Perception component
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UAIPerceptionComponent* AIPerceptionComponent;
	// Sight sense config
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UAISenseConfig_Sight* SightConfig;

	
public:

	AShooterAIController(const FObjectInitializer& ObjectInitializer);
	
protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	UFUNCTION()
	virtual void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus const Stimulus);
	
	UPROPERTY(EditDefaultsOnly, Category="AI")
	TObjectPtr<UBehaviorTree> TreeAsset;
	
};
