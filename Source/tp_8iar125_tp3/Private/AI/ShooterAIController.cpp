#include "AI/ShooterAIController.h"

#include "ShooterCharacter.h"
#include "AI/AIState.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

void AShooterAIController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus const Stimulus)
{
	const AShooterCharacter* ShootCharacter = Cast<AShooterCharacter>(Actor);

	if (!ShootCharacter)
		return;

	UBlackboardComponent* BlackboardComponent = GetBlackboardComponent();

	if (!BlackboardComponent)
		return;

	if (Stimulus.Type == UAISense::GetSenseID<UAISense_Sight>())
	{
		if (Stimulus.WasSuccessfullySensed())
		{
			// Follow target
			SetState(EAIState::Attack);
			BlackboardComponent->SetValueAsObject("Target", Actor);
		}
		else
		{
			// Go to last position
			BlackboardComponent->SetValueAsObject("Target", nullptr);
			BlackboardComponent->SetValueAsVector("NextPosition", Stimulus.StimulusLocation);
		}
	}
}

void AShooterAIController::OnTargetPerceptionForgotten(AActor* Actor)
{
	// Revert to explore
	SetState(EAIState::Explore);
}

void AShooterAIController::SetState(EAIState NewState)
{
	UBlackboardComponent* BlackboardComponent = GetBlackboardComponent();

	if (!BlackboardComponent)
		return;

	BlackboardComponent->SetValueAsEnum("State", static_cast<uint8>(NewState));
}

AShooterAIController::AShooterAIController(const FObjectInitializer&)
{
	const auto AIPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComponent"));
	SetPerceptionComponent(*AIPerceptionComponent);
}

void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();

	check(PerceptionComponent);
	PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(
		this,
		&AShooterAIController::OnTargetPerceptionUpdated
	);
	PerceptionComponent->OnTargetPerceptionForgotten.AddDynamic(
		this,
		&AShooterAIController::OnTargetPerceptionForgotten
	);
}

void AShooterAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (TreeAsset)
		RunBehaviorTree(TreeAsset);
}
