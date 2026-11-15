#include "TeamSubsystem.h"

void UTeamSubsystem::SetRelationships(UTeamRelationships* NewRelationships)
{
	Relationships = NewRelationships;
}

ETeamRelationType UTeamSubsystem::GetRelationship(const UTeamDefinition* A, const UTeamDefinition* B) const
{
	if (!Relationships)
		return ETeamRelationType::Neutral;

	return Relationships->GetRelationship(A, B);
}
