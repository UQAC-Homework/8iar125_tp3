// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/ShooterAIController.h"

#include "BehaviorTree/BehaviorTreeComponent.h"

AShooterAIController::AShooterAIController(const FObjectInitializer& ObjectInitializer)
{
	
}

void AShooterAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	if (TreeAsset)
	{
		RunBehaviorTree(TreeAsset);
	}
		
}
