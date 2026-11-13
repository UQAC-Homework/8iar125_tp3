#pragma once

#include "CoreMinimal.h"
#include "ETeam.h"
#include "Components/ActorComponent.h"
#include "TeamComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTeamChangedDelegate, ETeam, NewTeam);

/// Component responsible to assign a team to an actor
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TEAMSYSTEM_API UTeamComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Setter=SetTeam, Category = "Team")
	TEnumAsByte<ETeam> Team;

	UPROPERTY(BlueprintAssignable, Category = "Team")
	FOnTeamChangedDelegate OnTeamChanged;

public:
	UTeamComponent();

	/// Sets the team of this component to the given team
	UFUNCTION(BlueprintCallable, Category = "Team")
	void SetTeam(ETeam NewTeam);
};
