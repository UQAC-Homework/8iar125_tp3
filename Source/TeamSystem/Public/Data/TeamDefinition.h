#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TeamDefinition.generated.h"

/// Defines the unique properties of a team
UCLASS(BlueprintType)
class TEAMSYSTEM_API UTeamDefinition : public UPrimaryDataAsset
{
	GENERATED_BODY()

protected:
	/// Color that represents the team
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FLinearColor Color = FLinearColor::White;
};
