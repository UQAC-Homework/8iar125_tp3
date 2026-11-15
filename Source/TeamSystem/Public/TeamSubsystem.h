#pragma once

#include "CoreMinimal.h"
#include "Data/TeamRelationships.h"
#include "Subsystems/WorldSubsystem.h"
#include "TeamSubsystem.generated.h"

UCLASS()
class TEAMSYSTEM_API UTeamSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

	UPROPERTY(Transient)
	TObjectPtr<UTeamRelationships> Relationships;

public:
	/// Sets the relationships to use for this world
	UFUNCTION(BlueprintCallable, Category="Team")
	void SetRelationships(UTeamRelationships* NewRelationships);

	/// Gets the relationship of the first team towards the second one
	ETeamRelationType GetRelationship(const UTeamDefinition* A, const UTeamDefinition* B) const;
};
