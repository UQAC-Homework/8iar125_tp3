#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spawner.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSpawned, AActor*, Actor);

UCLASS()
class TP_8IAR125_TP3_API ASpawner : public AActor
{
	GENERATED_BODY()

	/// Called when this spawner spawned an actor 
	UPROPERTY(BlueprintAssignable, Category=Spawn)
	FOnSpawned OnSpawned;
	
protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	ASpawner();

	/// Spawns a new instance of the given class for the given controller
	void Spawn(AController* Controller, TSubclassOf<APawn> PawnClass) const;
};
