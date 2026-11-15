#include "Spawn/Spawner.h"

#include "Spawn/SpawningSubsystem.h"

void ASpawner::BeginPlay()
{
	Super::BeginPlay();

	const auto World = GetWorld();
	check(World);

	const auto SpawnerSystem = World->GetSubsystem<USpawningSubsystem>();

	if (SpawnerSystem)
		SpawnerSystem->RegisterSpawner(this);
}

void ASpawner::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	const auto World = GetWorld();
	check(World);

	const auto SpawnerSystem = World->GetSubsystem<USpawningSubsystem>();

	if (SpawnerSystem)
		SpawnerSystem->UnregisterSpawner(this);
}

ASpawner::ASpawner()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASpawner::Spawn(AController* Controller, TSubclassOf<APawn> PawnClass) const
{
	UE_LOG(LogTemp, Warning, TEXT("RespawnAs: controller=%s class=%s"),
	   *GetNameSafe(Controller), *GetNameSafe(PawnClass));

	if (!Controller)
	{
		UE_LOG(
			LogTemp,
			Warning,
			TEXT("Failed to spawn as the controller was invalid.")
		);
		return;
	}

	if (!PawnClass)
	{
		UE_LOG(
			LogTemp,
			Error,
			TEXT("Failed to spawn as no class was provided.")
		);
		return;
	}

	const auto World = GetWorld();
	check(World);

	const auto StartLocation = GetActorLocation();
	const auto StartRotation = GetActorRotation();

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	const auto Actor = World->SpawnActor(
		PawnClass,
		&StartLocation,
		&StartRotation,
		SpawnParams
	);

	if (!Actor)
	{
		UE_LOGF(
			LogTemp,
			Warning,
			"Failed to spawn actor of type '%ls'.",
			*PawnClass->GetName()
		);
		return;
	}

	if (OnSpawned.IsBound())
		OnSpawned.Broadcast(Actor);

	const auto Pawn = Cast<APawn>(Actor);

	if (!Pawn)
	{
		UE_LOGF(
			LogTemp,
			Warning,
			"Cannot possess an actor of type '%ls'.",
			*PawnClass->GetName()
		);
		return;
	}

	Controller->Possess(Pawn);
	UE_LOG(LogTemp, Warning, TEXT("Spawned %s at %s, controller pawn now = %s"),
	*GetNameSafe(Pawn), *StartLocation.ToString(), *GetNameSafe(Controller->GetPawn()));
}
