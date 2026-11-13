#pragma once

#include "CoreMinimal.h"
#include "ETeam.generated.h"

/// List of possible teams
UENUM(BlueprintType)
enum class ETeam : uint8
{
	None UMETA(DisplayName = "None"),
	Red UMETA(DisplayName = "Red"),
	Blue UMETA(DisplayName = "Blue"),
};
