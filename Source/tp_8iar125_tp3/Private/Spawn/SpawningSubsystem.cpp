#include "Spawn/SpawningSubsystem.h"

void USpawningSubsystem::RegisterSpawner(ASpawner* Spawner)
{
	if (!Spawner)
		return;

	Spawners.Add(Spawner);
}

void USpawningSubsystem::UnregisterSpawner(ASpawner* Spawner)
{
	if (!Spawner)
		return;

	Spawners.RemoveSingle(Spawner);
}

void USpawningSubsystem::RespawnAs(AController* Controller, const TSubclassOf<APawn> PawnClass)
{
	Spawners[0]->Spawn(Controller, PawnClass);
}
