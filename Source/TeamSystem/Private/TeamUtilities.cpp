#include "TeamUtilities.h"

#include "TeamComponent.h"
#include "TeamSubsystem.h"
#include "GameFramework/PlayerState.h"

UTeamComponent* UTeamUtilities::GetTeamComponent(const AActor* InActor)
{
	if (!InActor)
		return nullptr;

	const auto SelfComponent = InActor->FindComponentByClass<UTeamComponent>();

	if (SelfComponent)
		return SelfComponent;

	const auto Pawn = Cast<APawn>(InActor);

	if (!Pawn)
		return nullptr;

	const auto Controller = Pawn->GetController();

	if (Controller)
	{
		const auto Comp = GetTeamComponent(Controller);
		
		if (Comp)
			return Comp;
	}

	const auto PlayerState = Pawn->GetPlayerState();

	if (PlayerState)
	{
		const auto Comp = GetTeamComponent(PlayerState);
		
		if (Comp)
			return Comp;
	}

	return nullptr;
}

UTeamDefinition* UTeamUtilities::GetTeam(const AActor* InActor)
{
	const auto TeamComponent = GetTeamComponent(InActor);

	if (!TeamComponent)
		return nullptr;

	return TeamComponent->GetTeam();
}

ETeamRelationType UTeamUtilities::GetRelationship(const AActor* From, const AActor* To)
{
	if (!IsValid(From))
		return ETeamRelationType::Neutral;

	const auto World = From->GetWorld();
	check(World);

	const auto Subsystem = World->GetSubsystem<UTeamSubsystem>();

	if (!Subsystem)
		return ETeamRelationType::Neutral;

	const auto TeamFrom = GetTeam(From);
	const auto TeamTo = GetTeam(To);

	return Subsystem->GetRelationship(TeamFrom, TeamTo);
}

TArray<AActor*> UTeamUtilities::KeepOnlyRelationship(const TArray<AActor*>& InActors, const AActor* Viewer,
                                                     const ETeamRelationType Type)
{
	TArray<AActor*> FilteredActors;

	if (!IsValid(Viewer))
		return FilteredActors;

	FilteredActors.Reserve(InActors.Num());

	for (AActor* Actor : InActors)
	{
		if (!IsValid(Actor))
			continue;

		if (GetRelationship(Viewer, Actor) == Type)
			FilteredActors.Add(Actor);
	}

	return FilteredActors;
}
