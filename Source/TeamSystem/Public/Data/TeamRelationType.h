#pragma once

#include "CoreMinimal.h"
#include "TeamRelationType.generated.h"

/// List of possible relation type a team can have towards another
UENUM(BlueprintType)
enum class ETeamRelationType : uint8
{
	Ally,
	Neutral,
	Enemy
};