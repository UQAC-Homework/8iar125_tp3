#pragma once

#include "CoreMinimal.h"
#include "TeamComponent.h"
#include "Data/TeamDefinition.h"
#include "Data/TeamRelationType.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TeamUtilities.generated.h"

UCLASS()
class TEAMSYSTEM_API UTeamUtilities : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/// Gets the team component of the given actor
	UFUNCTION(BlueprintPure, Category="Team", meta=(DefaultToSelf="InActor"))
	static UTeamComponent* GetTeamComponent(const AActor* InActor);

	/// Gets the team of the given actor
	UFUNCTION(BlueprintPure, Category="Team", meta=(DefaultToSelf="InActor"))
	static UTeamDefinition* GetTeam(const AActor* InActor);

	/// Gets the relationship between the given actors
	UFUNCTION(BlueprintPure, Category="Team", meta=(DefaultToSelf="From"))
	static ETeamRelationType GetRelationship(const AActor* From, const AActor* To);

	/// Filters the actors that do not have the given relationship with the given viewer
	UFUNCTION(BlueprintPure, Category="Team", meta=(DeterminesOutputType="InActors", DefaultToSelf="Viewer"))
	static TArray<AActor*> KeepOnlyRelationship(
		const TArray<AActor*>& InActors,
		const AActor* Viewer,
		ETeamRelationType Type
	);
};
