#include "TeamComponent.h"

UTeamComponent::UTeamComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	Team = ETeam::None;
}

ETeam UTeamComponent::GetTeam() const
{
	return Team;
}

void UTeamComponent::SetTeam(const ETeam NewTeam)
{
	if (Team == NewTeam)
		return;

	Team = NewTeam;

	if (OnTeamChanged.IsBound())
		OnTeamChanged.Broadcast(Team);
}
