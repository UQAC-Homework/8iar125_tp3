#include "GameModes/ShooterGameMode.h"

#include "TeamSubsystem.h"
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

void AShooterGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
	
	const auto World = GetWorld();
	check(World);
	
	const auto Teams = World->GetSubsystem<UTeamSubsystem>();

	if (Teams)
		Teams->SetRelationships(TeamRelationships);
}
