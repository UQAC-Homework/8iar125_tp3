#include "Data/TeamRelationships.h"

ETeamRelationType UTeamRelationships::GetRelationship(const UTeamDefinition* A, const UTeamDefinition* B) const
{
	if (!A || !B)
		return ETeamRelationType::Neutral;

	if (A == B)
		return ETeamRelationType::Ally;

	// ReSharper disable once CppUseStructuredBinding
	for (const auto& Relation : RelationshipOverrides)
	{
		const auto Emitter = Relation.Emitter;

		if (Emitter != A)
			continue;

		const auto Receiver = Relation.Receiver;

		if (Receiver != B)
			continue;

		return Relation.Type;
	}

	return DefaultRelationship;
}
