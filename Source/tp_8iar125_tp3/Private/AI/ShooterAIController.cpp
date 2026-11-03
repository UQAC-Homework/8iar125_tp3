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
			BlackboardComponent->SetValueAsEnum("State", static_cast<uint8>(EAIState::Attack));
			BlackboardComponent->SetValueAsObject("Target", Actor);
		}
		else
		{
			BlackboardComponent->SetValueAsObject("Target", nullptr);
			BlackboardComponent->SetValueAsVector("NextPosition", Stimulus.StimulusLocation);
		}
	}
}

void AShooterAIController::OnTargetPerceptionForgotten(AActor* Actor)
{
	UBlackboardComponent* BlackboardComponent = GetBlackboardComponent();

	if (!BlackboardComponent)
		return;

	BlackboardComponent->SetValueAsEnum("State", static_cast<uint8>(EAIState::Explore));
}

AShooterAIController::AShooterAIController(const FObjectInitializer&)
{
	const auto PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("PerceptionComponent"));
	SetPerceptionComponent(*PerceptionComponent);

	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
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
