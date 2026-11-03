#pragma once

#include "CoreMinimal.h"
#include "AiState.generated.h"

UENUM(BlueprintType)
enum class EAiState : uint8
{
	Attack = 0,
	Cover = 1,
	Explore = 2
};
