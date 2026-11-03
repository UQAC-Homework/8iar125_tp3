#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "Perception/AISenseConfig_Sight.h"
#include "ShooterAIController.generated.h"

UCLASS()
class TP_8IAR125_TP3_API AShooterAIController : public AAIController
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=AI, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UAISenseConfig_Sight> SightConfig;

	UPROPERTY(EditDefaultsOnly, Category=AI)
	TObjectPtr<UBehaviorTree> TreeAsset;

	/// Called when a stimulus has changed
	UFUNCTION()
	void OnTargetPerceptionUpdated(AActor* Actor, FAIStimulus const Stimulus);

	/// Called when a stimulus is forgotten
	UFUNCTION()
	void OnTargetPerceptionForgotten(AActor* Actor);

public:
	explicit AShooterAIController(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
};
