#pragma once

#include "CoreMinimal.h"
#include "TeamDefinition.h"
#include "TeamRelationship.h"
#include "TeamRelationType.h"
#include "Engine/DataAsset.h"
#include "TeamRelationships.generated.h"

/// Defines the relationship between teams
UCLASS(BlueprintType)
class TEAMSYSTEM_API UTeamRelationships : public UPrimaryDataAsset
{
	GENERATED_BODY()

	/// Default relationship of the teams
	UPROPERTY(EditDefaultsOnly)
	ETeamRelationType DefaultRelationship = ETeamRelationType::Enemy;

	/// Specific relationship type of team 
	UPROPERTY(EditDefaultsOnly)
	TArray<FTeamRelationship> RelationshipOverrides;

public:
	/// Gets the relationship of the first given team towards the second given team
	ETeamRelationType GetRelationship(
		const UTeamDefinition* A,
		const UTeamDefinition* B
	) const;
};
