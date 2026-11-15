#pragma once

#include "CoreMinimal.h"
#include "TeamRelationType.h"
#include "TeamDefinition.h"
#include "TeamRelationship.generated.h"

/// Defines a relationship between two teams
USTRUCT(BlueprintType)
struct TEAMSYSTEM_API FTeamRelationship
{
	GENERATED_BODY()
	
public:
	/// Team that emits the relationship
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UTeamDefinition> Emitter;

	/// Team that receives the relationship
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UTeamDefinition> Receiver;
	
	/// Type of the relationship
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ETeamRelationType Type = ETeamRelationType::Neutral;
};
