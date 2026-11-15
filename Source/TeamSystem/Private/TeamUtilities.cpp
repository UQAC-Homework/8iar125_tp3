#include "TeamUtilities.h"

#include "TeamComponent.h"
#include "TeamSubsystem.h"

UTeamDefinition* UTeamUtilities::GetTeam(const AActor* InActor)
{
	if (!IsValid(InActor))
		return nullptr;

	const auto TeamComponent = InActor->FindComponentByClass<UTeamComponent>();

	if (!IsValid(TeamComponent))
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
