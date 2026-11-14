#include "TeamUtilities.h"

#include "TeamComponent.h"

ETeam UTeamUtilities::GetTeam(const AActor* InActor)
{
	if (!IsValid(InActor))
		return ETeam::None;

	const auto TeamComponent = InActor->FindComponentByClass<UTeamComponent>();

	if (!IsValid(TeamComponent))
		return ETeam::None;

	return TeamComponent->GetTeam();
}

TArray<AActor*> UTeamUtilities::KeepOnlyTeam(const TArray<AActor*>& InActors, const ETeam TargetTeam)
{
	TArray<AActor*> FilteredActors;
	FilteredActors.Reserve(InActors.Num());

	for (AActor* Actor : InActors)
	{
		const auto Team = GetTeam(Actor);

		if (Team == TargetTeam)
			FilteredActors.Add(Actor);
	}

	return FilteredActors;
}
