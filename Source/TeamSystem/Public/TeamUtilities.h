#pragma once

#include "CoreMinimal.h"
#include "ETeam.h"
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
	static ETeam GetTeam(const AActor* InActor);

	/// Filters all actors that are not on the given team
	UFUNCTION(BlueprintPure, Category=TEAM_CATEGORY, meta = (DeterminesOutputType = "InActors"))
	static TArray<AActor*> KeepOnlyTeam(const TArray<AActor*>& InActors, ETeam TargetTeam);
};
