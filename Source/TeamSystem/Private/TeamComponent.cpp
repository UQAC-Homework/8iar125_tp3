#include "TeamComponent.h"

UTeamComponent::UTeamComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	Team = nullptr;
}

UTeamDefinition* UTeamComponent::GetTeam() const
{
	return Team;
}

void UTeamComponent::SetTeam(UTeamDefinition* NewTeam)
{
	if (Team == NewTeam)
		return;

	Team = NewTeam;

	if (OnTeamChanged.IsBound())
		OnTeamChanged.Broadcast(Team);
}
