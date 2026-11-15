#pragma once

#include "CoreMinimal.h"
#include "Data/TeamDefinition.h"
#include "Data/TeamRelationType.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TeamUtilities.generated.h"

#define TEAM_CATEGORY "Utilities/Team"

UCLASS()
class TEAMSYSTEM_API UTeamUtilities : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/// Gets the team of the given actor
	UFUNCTION(BlueprintPure, Category=TEAM_CATEGORY)
	static UTeamDefinition* GetTeam(const AActor* InActor);

	/// Gets the relationship between the given actors
	UFUNCTION(BlueprintPure, Category=TEAM_CATEGORY)
	static ETeamRelationType GetRelationship(const AActor* From, const AActor* To);

	/// Filters the actors that do not have the given relationship with the given viewer
	UFUNCTION(BlueprintPure, Category=TEAM_CATEGORY, meta=(DeterminesOutputType="InActors"))
	static TArray<AActor*> KeepOnlyRelationship(
		const TArray<AActor*>& InActors,
		const AActor* Viewer,
		ETeamRelationType Type
	);
};
