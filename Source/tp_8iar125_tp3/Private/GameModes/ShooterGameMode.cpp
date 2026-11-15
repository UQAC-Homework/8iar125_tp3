#include "GameModes/ShooterGameMode.h"

#include "AIController.h"
#include "AI/ShooterAIController.h"
#include "Spawn/SpawningSubsystem.h"

class USpawningSubsystem;

ETeam AShooterGameMode::GetEnemyTeam_Implementation(ETeam Team)
{
	return ETeam::None;
}

void AShooterGameMode::HandleDeath_Implementation(AController* Controller, TSubclassOf<APawn> PawnClass)
{
	const auto World = GetWorld();
	check(World);
  
	const auto SpawnSystem = World->GetSubsystem<USpawningSubsystem>();
	
	if (!SpawnSystem)
		return;

	SpawnSystem->RespawnAs(Controller, PawnClass);
}
