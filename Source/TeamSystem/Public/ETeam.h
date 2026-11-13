#pragma once

/// List of possible teams
UENUM()
enum ETeam : uint8
{
	None UMETA(DisplayName = "None"),
	Red UMETA(DisplayName = "Red"),
	Blue UMETA(DisplayName = "Blue"),
};
