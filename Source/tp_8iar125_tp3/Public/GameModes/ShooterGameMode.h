#pragma once

#include "CoreMinimal.h"
#include "Data/TeamRelationships.h"
#include "GameFramework/GameModeBase.h"
#include "ShooterGameMode.generated.h"

UCLASS()
class TP_8IAR125_TP3_API AShooterGameMode : public AGameModeBase
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category="Teams")
	TObjectPtr<UTeamRelationships> TeamRelationships;

public:
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

	/// Handles the given controller when its pawn was killed
	UFUNCTION(BlueprintNativeEvent, Category=Spawn)
	void HandleDeath(AController* Controller, TSubclassOf<APawn> PawnClass);
};
