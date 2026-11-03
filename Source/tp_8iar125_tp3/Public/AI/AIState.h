#pragma once

#include "CoreMinimal.h"
#include "AIState.generated.h"

UENUM(BlueprintType)
enum class EAIState : uint8
{
	Attack = 0,
	Cover = 1,
	Explore = 2
};
