// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/ShooterAIController.h"

#include "ShooterCharacter.h"
#include "AI/AIState.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

AShooterAIController::AShooterAIController(const FObjectInitializer& ObjectInitializer)
{
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComponent"));
	SetPerceptionComponent(*PerceptionComponent);
	// Create the sight config
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	
	
	Blackboard = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackBoardComponent"));
	
	BrainComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
	
	
	
	
}

void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();
	
	PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this,&AShooterAIController::OnTargetPerceptionUpdated);
}

void AShooterAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	if (TreeAsset)
	{
		RunBehaviorTree(TreeAsset);
	}
		
}

void AShooterAIController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus const Stimulus)
{
	AShooterCharacter* ShootCharacter = Cast<AShooterCharacter>(Actor);
	
	if (!ShootCharacter)
		return;
	
	UBlackboardComponent* BlackboardComponent = GetBlackboardComponent();
	if (!BlackboardComponent)
	{
		return;
	}
	
	if (Stimulus.Type == UAISense::GetSenseID<UAISense_Sight>())
	{
		// if stimulus is sight, check if stimulus is sensed
		if (Stimulus.WasSuccessfullySensed())
		{
			// Set can see player to true
			
			BlackboardComponent->SetValueAsEnum("State",static_cast<uint8>(EAiState::Attack));
			BlackboardComponent->SetValueAsObject("Target", Actor);
		}
		else
		{
			//BlackboardComponent->SetValueAsBool("CanSeePlayer", false);
			BlackboardComponent->SetValueAsEnum("State",static_cast<uint8>(EAiState::Explore));
			BlackboardComponent->SetValueAsObject("Target", nullptr);
		}
	}
}
