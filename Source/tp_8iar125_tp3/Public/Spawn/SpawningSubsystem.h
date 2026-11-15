#pragma once

#include "CoreMinimal.h"
#include "Spawner.h"
#include "Subsystems/WorldSubsystem.h"
#include "SpawningSubsystem.generated.h"

UCLASS()
class TP_8IAR125_TP3_API USpawningSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

	UPROPERTY(VisibleInstanceOnly, Category=Spawning)
	TArray<ASpawner*> Spawners;

public:
	/// Registers the given spawner
	void RegisterSpawner(ASpawner* Spawner);

	/// Unregisters the given spawner
	void UnregisterSpawner(ASpawner* Spawner);
	
	/// Respawns the given controller as an instance of the given pawn
	void RespawnAs(AController* Controller, TSubclassOf<APawn> PawnClass);
};
