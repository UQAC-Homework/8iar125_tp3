#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Data/TeamDefinition.h"
#include "TeamComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTeamChangedDelegate, UTeamDefinition*, NewTeam);

/// Component responsible to assign a team to an actor
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TEAMSYSTEM_API UTeamComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Getter=GetTeam, Setter=SetTeam, Category = "Team")
	TObjectPtr<UTeamDefinition> Team;

	/// Called when the team has changed
	UPROPERTY(BlueprintAssignable, Category = "Team")
	FOnTeamChangedDelegate OnTeamChanged;

public:
	UTeamComponent();

	/// Gets the current team of this component
	UFUNCTION(BlueprintCallable, Category = "Team")
	UTeamDefinition* GetTeam() const;

	/// Sets the team of this component to the given team
	UFUNCTION(BlueprintCallable, Category = "Team")
	void SetTeam(UTeamDefinition* NewTeam);
};
