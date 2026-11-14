#pragma once

#include "CoreMinimal.h"
#include "ETeam.h"
#include "GameFramework/GameModeBase.h"
#include "ShooterGameMode.generated.h"

UCLASS()
class TP_8IAR125_TP3_API AShooterGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	/// Gets the team enemy of the given team
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category=Team)
	ETeam GetEnemyTeam(ETeam Team);
};
