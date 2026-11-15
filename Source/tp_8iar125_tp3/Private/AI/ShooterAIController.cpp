#include "AI/ShooterAIController.h"

#include "ShooterCharacter.h"
#include "TeamUtilities.h"
#include "AI/AIState.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISense_Damage.h"

void AShooterAIController::OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus const Stimulus)
{
	const auto Pawn = GetPawn();

	if (!Pawn)
		return;

	const AShooterCharacter* ShootCharacter = Cast<AShooterCharacter>(Actor);

	if (!ShootCharacter)
		return;

	const auto SelfTeam = UTeamUtilities::GetTeam(Pawn);
	const auto OtherTeam = UTeamUtilities::GetTeam(Actor);

	if (SelfTeam == OtherTeam)
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
	else if (Stimulus.Type == UAISense::GetSenseID<UAISense_Damage>())
	{
		BlackboardComponent->SetValueAsVector("NextPosition", Stimulus.StimulusLocation);
		SetState(EAIState::Cover);
		//OnGettingAttacked()
	}
}

void AShooterAIController::OnTargetPerceptionForgotten(AActor* Actor)
{
	// Revert to explore
	SetState(EAIState::Explore);
}

void AShooterAIController::IsGettingAttacked(AActor* AttackerActor)
{
	SetState(EAIState::Cover);

	UBlackboardComponent* BlackboardComponent = GetBlackboardComponent();

	if (!BlackboardComponent)
		return;

	//BlackboardComponent->SetValueAsObject("Target", nullptr);
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
