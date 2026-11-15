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
	if (Spawners.IsEmpty())
	{
		UE_LOG(
			LogTemp,
			Error,
			TEXT("No spawner available.")
		);
		return;
	}

	const auto Index = FMath::RandRange(0, Spawners.Num() - 1);
	Spawners[Index]->Spawn(Controller, PawnClass);
}
